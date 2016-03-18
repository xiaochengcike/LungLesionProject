/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    FMandGACLevelSetSegmentationModule.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkFMandGACLevelSetSegmentationModule_h
#define __itkFMandGACLevelSetSegmentationModule_h

#include "itkSinglePhaseLevelSetSegmentationModule.h"
#include "itkFastMarchingSegmentationModule.h"
#include "itkGeodesicActiveContourLevelSetSegmentationModule.h"
#include "itkLandmarkSpatialObject.h"
#include "itkSPFLevelSetSegmentationModule.h"

namespace itk
{

/** \class FMandGACLevelSetSegmentationModule
 * \brief This class applies the GeodesicActiveContourLevelSet segmentation
 * method.
 *
 * SpatialObjects are used as inputs and outputs of this class.
 *
 * \ingroup SpatialObjectFilters
 * \ingroup ITKLesionSizingToolkit
 */
template <unsigned int NDimension>
class ITK_EXPORT FMandGACLevelSetSegmentationModule 
	: public SinglePhaseLevelSetSegmentationModule<NDimension>
{
public:
  /** Standard class typedefs. */
  typedef FMandGACLevelSetSegmentationModule                Self;
  typedef SinglePhaseLevelSetSegmentationModule<NDimension>       Superclass;
  typedef SmartPointer<Self>                                      Pointer;
  typedef SmartPointer<const Self>                                ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(FMandGACLevelSetSegmentationModule, SinglePhaseLevelSetSegmentationModule);

  /** Dimension of the space */
  itkStaticConstMacro(Dimension, unsigned int, NDimension);

  /** Type of spatialObject that will be passed as input and output of this
   * segmentation method. */
  typedef typename Superclass::SpatialObjectType         SpatialObjectType;
  typedef typename Superclass::SpatialObjectPointer      SpatialObjectPointer;

  /** Types of images and spatial objects inherited from the superclass. */
  typedef typename Superclass::OutputPixelType           OutputPixelType;
  typedef typename Superclass::InputImageType            InputImageType;
  typedef typename Superclass::FeatureImageType          FeatureImageType;
  typedef typename Superclass::OutputImageType           OutputImageType;
  typedef typename Superclass::FeatureSpatialObjectType  FeatureSpatialObjectType;
  typedef typename Superclass::OutputSpatialObjectType   OutputSpatialObjectType;

  /** Type of the input set of seed points. They are stored in a Landmark Spatial Object. */
  typedef LandmarkSpatialObject< NDimension >                  InputSpatialObjectType;

  /** Set the Fast Marching algorithm Stopping Value. The Fast Marching
   * algorithm is terminated when the value of the smallest trial point
   * is greater than the stopping value. */
  virtual void SetStoppingValue( double d )
    { m_FastMarchingModule->SetStoppingValue( d ); }
  virtual double GetStoppingValue() const
    { return m_FastMarchingModule->GetStoppingValue(); }

  /** Set the Fast Marching algorithm distance from seeds. */
  virtual void SetDistanceFromSeeds( double d )
    { m_FastMarchingModule->SetDistanceFromSeeds( d ); }
  virtual double GetDistanceFromSeeds() const
    { return m_FastMarchingModule->GetDistanceFromSeeds(); }

protected:
  FMandGACLevelSetSegmentationModule();
  virtual ~FMandGACLevelSetSegmentationModule();
  void PrintSelf(std::ostream& os, Indent indent) const;

  /** Method invoked by the pipeline in order to trigger the computation of
   * the segmentation. */
  void  GenerateData ();

  typedef  FastMarchingSegmentationModule< Dimension > FastMarchingModuleType;
  typename FastMarchingModuleType::Pointer m_FastMarchingModule;
  typedef  GeodesicActiveContourLevelSetSegmentationModule< Dimension > GeodesicActiveContourLevelSetModuleType;
  typename GeodesicActiveContourLevelSetModuleType::Pointer m_GeodesicActiveContourLevelSetModule;
  typedef  SPFLevelSetSegmentationModule< Dimension >  SPFLevelSetModuleType;
  typename SPFLevelSetModuleType::Pointer  m_SPFLevelSetModule;

private:
  FMandGACLevelSetSegmentationModule(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
# include "itkFMandGACLevelSetSegmentationModule.hxx"
#endif

#endif