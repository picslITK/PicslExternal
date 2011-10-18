itk_module_test()
set(ITKPicslExternalTests
  itkANTSSparseNeighborhoodCorrelationImageToImageObjectRegistrationTest.cxx
  itkANTSSparseNeighborhoodCorrelationImageToImageObjectMetricTest.cxx
  itkQuasiNewtonRegistrationTest.cxx
  itkQuasiNewtonDemonsRegistrationTest.cxx
  itkQuasiNewtonObjectOptimizerTest.cxx
  itkPolyAffineTransformTest.cxx
  itkANTSNeighborhoodCorrelationImageToImageObjectRegistrationTest2.cxx
  itkANTSNeighborhoodCorrelationImageToImageObjectRegistrationTest3.cxx
  itkANTSNeighborhoodCorrelationImageToImageObjectRegistrationTest4.cxx
  # On hold until class is updated
  #itkDemonsVectorImageToVectorImageObjectRegistrationTest.cxx
  #itkDemonsVectorImageToVectorImageObjectMetricTest.cxx
)

set(INPUTDATA ${ITK_DATA_ROOT}/Input)
set(BASELINE_ROOT ${ITK_DATA_ROOT}/Baseline)
set(TEMP ${ITK_TEST_OUTPUT_DIR})

CreateTestDriver(ITKPicslExternal  "${ITKPicslExternal-Test_LIBRARIES}" "${ITKPicslExternalTests}")

# On hold until class is updated
#itk_add_test(NAME itkDemonsVectorImageToVectorImageObjectMetricTest
#      COMMAND ITKPicslExternalTestDriver
#      itkDemonsVectorImageToVectorImageObjectMetricTest)

itk_add_test(NAME itkANTSNeighborhoodCorrelationImageToImageObjectMetricTest
      COMMAND ITKPicslExternalTestDriver
      itkANTSNeighborhoodCorrelationImageToImageObjectMetricTest)

# NOTE - this is waiting for new testing data images to be added
#itk_add_test(NAME itkDemonsImageToImageObjectRegistrationTest
#      COMMAND ITKPicslExternalTestDriver
#      --compare ${TEMP}/itkDemonsImageToImageObjectRegistrationTest_out.nii.gz
#                DATA{Baseline/#itkDemonsImageToImageObjectRegistrationTest_r62r85_Out.nii.gz}
#      itkDemonsImageToImageObjectRegistrationTest
#      DATA{Input/r62slice.nii} DATA{Input/r85slice.nii}
#      ${TEMP}/itkDemonsImageToImageObjectRegistrationTest_out.nii.gz)

#itk_add_test(NAME itkDemonsImageToImageObjectRegistrationTest2
#      COMMAND ITKPicslExternalTestDriver
#      itkDemonsImageToImageObjectRegistrationTest2)

# itk_add_test(NAME itkANTSNeighborhoodCorrelationImageToImageObjectRegistrationTest3
#      COMMAND ITKPicslExternalTestDriver
#      itkANTSNeighborhoodCorrelationImageToImageObjectRegistrationTest3)


itk_add_test(NAME itkANTSSparseNeighborhoodCorrelationImageToImageObjectRegistrationTest
      COMMAND ITKPicslExternalTestDriver
      itkANTSSparseNeighborhoodCorrelationImageToImageObjectRegistrationTest)

itk_add_test(NAME itkANTSSparseNeighborhoodCorrelationImageToImageObjectMetricTest
      COMMAND ITKPicslExternalTestDriver
      itkANTSSparseNeighborhoodCorrelationImageToImageObjectMetricTest)

itk_add_test(NAME itkQuasiNewtonDemonsRegistrationTest
      COMMAND ITKPicslExternalTestDriver
      itkQuasiNewtonDemonsRegistrationTest
      ${ITK_SOURCE_DIR}/Examples/Data/r62slice.nii
      ${ITK_SOURCE_DIR}/Examples/Data/r85slice.nii
      ${TEMP}/QNDemonsOutput.nii
      )

itk_add_test(NAME itkQuasiNewtonRegistrationTest
      COMMAND ITKPicslExternalTestDriver
      itkQuasiNewtonRegistrationTest
      #${ITK_SOURCE_DIR}/Examples/Data/r62slice.nii
      #${ITK_SOURCE_DIR}/Examples/Data/r85slice.nii
      #${TEMP}/QNOptOutput.nii
      )

itk_add_test(NAME itkPolyAffineTransformTest
      COMMAND ITKPicslExternalTestDriver
      itkPolyAffineTransformTest
      )

itk_add_test(NAME itkQuasiNewtonObjectOptimizerTest
      COMMAND ITKPicslExternalTestDriver
      itkQuasiNewtonObjectOptimizerTest)

#TODO
# itk_add_test(NAME itkANTSNeighborhoodCorrelationImageToImageObjectRegistrationTest2
#      COMMAND ITKPicslExternalTestDriver
#      itkANTSNeighborhoodCorrelationImageToImageObjectRegistrationTest2)
