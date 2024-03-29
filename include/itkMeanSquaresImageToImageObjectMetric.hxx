/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkMeanSquaresImageToImageObjectMetric.hxx,v $
  Language:  C++
  Date:      $Date: $
  Version:   $Revision: $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkMeanSquaresImageToImageObjectMetric_hxx
#define __itkMeanSquaresImageToImageObjectMetric_hxx

#include "itkMeanSquaresImageToImageObjectMetric.h"
#include "vnl/vnl_math.h"

namespace itk
{

/**
 * Constructor
 */
template < class TFixedImage, class TMovingImage, class TVirtualImage >
MeanSquaresImageToImageObjectMetric<TFixedImage,TMovingImage,TVirtualImage>
::MeanSquaresImageToImageObjectMetric()
{
}

template < class TFixedImage, class TMovingImage, class TVirtualImage >
MeanSquaresImageToImageObjectMetric<TFixedImage,TMovingImage,TVirtualImage>
::~MeanSquaresImageToImageObjectMetric()
{
}

/*
 * GetValueAndDerivative
 */
template < class TFixedImage, class TMovingImage, class TVirtualImage >
void
MeanSquaresImageToImageObjectMetric<TFixedImage,TMovingImage,TVirtualImage>
::GetValueAndDerivative( MeasureType & value, DerivativeType & derivative) const
{
  // This starts threading, and will iterate over virtual image region and
  // call GetValueAndDerivativeProcessPoint.
  this->GetValueAndDerivativeThreadedExecute( derivative );

  // Sums up results from each thread, and optionally averages them.
  // Derivative results are written directly to \c derivative.
  this->GetValueAndDerivativeThreadedPostProcess( true /*doAverage*/ );

  value = this->GetValueResult();
}

/** This function computes the local voxel-wise contribution of
 *  the metric to the global integral of the metric/derivative.
 */
template < class TFixedImage, class TMovingImage, class TVirtualImage >
bool
MeanSquaresImageToImageObjectMetric<TFixedImage,TMovingImage,TVirtualImage>
::GetValueAndDerivativeProcessPoint(
                    const VirtualPointType &           virtualPoint,
                    const FixedImagePointType &,
                    const FixedImagePixelType &        fixedImageValue,
                    const FixedImageGradientType &,
                    const MovingImagePointType &,
                    const MovingImagePixelType &       movingImageValue,
                    const MovingImageGradientType & movingImageDerivatives,
                    MeasureType &                      metricValueReturn,
                    DerivativeType &                   localDerivativeReturn,
                    ThreadIdType                       threadID) const
{
  /** Only the voxelwise contribution given the point pairs. */
  FixedImagePixelType diff = movingImageValue - fixedImageValue;
  metricValueReturn = - diff * diff; //always assuming a maximizing function
  //if (virtualPoint[0]==188 && virtualPoint[1]==155)
  //if (virtualPoint[0]==256-142 && virtualPoint[1]==256-176)
  //  int tmpdbg=0;
  //static int tmpcount=0;
  //if (tmpcount < 256*256)
  //  std::cout << "diffImage(" << (int)(256-virtualPoint[0]) << ","
  //  << (int)(256-virtualPoint[1]) << ")=" << diff << ";" << std::endl; //tmpdbg
  //tmpcount++;

  /* Use a pre-allocated jacobian object for efficiency */
  typedef typename Superclass::JacobianType &   JacobianReferenceType;
  JacobianReferenceType movingJacobian = const_cast<JacobianReferenceType>(
    this->m_MovingTransformJacobianPerThread[threadID]);

  //FIXME: we may optimize the fixed transform as well
  //JacobianType & fixedJacobian =
  //                          this->m_FixedTransformJacobianPerThread[threadID];

  /** For dense transforms, this returns identity */
  this->m_MovingTransform->ComputeJacobianWithRespectToParameters(
                                                            virtualPoint,
                                                            movingJacobian);
  //FIXME: we may optimize the fixed transform as well
  //this->m_FixedTransform->ComputeJacobianWithRespectToParameters(
  //                                                          virtualPoint,
  //                                                          fixedJacobian);

  for ( unsigned int par = 0;
          par < this->GetNumberOfLocalParameters(); par++ )
  {
    double sum = 0.0;
    for ( unsigned int dim = 0; dim < this->MovingImageDimension; dim++ )
      {
        sum += 2.0 * diff * movingJacobian(dim, par) * movingImageDerivatives[dim];
      }
    //FIXME: we may optimize the fixed transform as well
    //for ( unsigned int dim = 0; dim < this->FixedImageDimension; dim++ )
    //  {
    //    sum -= 2.0 * diff * fixedJacobian(dim, par) * movingImageDerivatives[dim];
    //  }
    localDerivativeReturn[par] = - sum; //always assuming a maximizing function
  }
  //  std::cout << localDerivativeReturn << std::endl;
  // Return true if the point was used in evaluation
  return true;
}

/**
 * Print out internal information about this class
 */
template < class TFixedImage, class TMovingImage, class TVirtualImage  >
void
MeanSquaresImageToImageObjectMetric<TFixedImage,TMovingImage,TVirtualImage>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}

/**
 * Initialize
 */
template <class TFixedImage, class TMovingImage, class TVirtualImage>
void
MeanSquaresImageToImageObjectMetric<TFixedImage,TMovingImage,TVirtualImage>
::Initialize(void) throw ( ExceptionObject )
{
  this->Superclass::Initialize();
}

} // end namespace itk


#endif
