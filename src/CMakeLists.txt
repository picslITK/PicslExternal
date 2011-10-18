set(ITKPicslExternal_SRC
itkQuasiNewtonObjectOptimizer.cxx
itkQuasiNewtonLocalSupportObjectOptimizer.cxx
)

add_library(ITKPicslExternal ${ITKPicslExternal_SRC})
target_link_libraries(ITKPicslExternal
  ${ITKHighDimensionalOptimizers_LIBRARIES}
  ${ITKHighDimensionalMetrics_LIBRARIES}
  ${ITKRegistrationCommon_LIBRARIES}
  ${ITKOptimizers_LIBRARIES}
  ${ITKImageIntensity_LIBRARIES}
  ${ITKImageFunction_LIBRARIES}
  ${ITKImageGrid_LIBRARIES}
  ${ITKSpatialObjects_LIBRARIES}
  ${ITKSmoothing_LIBRARIES}
  ${ITKImageGradient_LIBRARIES}
  ${ITKImageFeature_LIBRARIES}
  ${ITKFiniteDifference_LIBRARIES}
   )
itk_module_target(ITKPicslExternal)
