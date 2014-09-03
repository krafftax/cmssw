#ifndef RecoLocalTracker_SiStripRecHitConverter_StripCPEfromTrackAngle_H
#define RecoLocalTracker_SiStripRecHitConverter_StripCPEfromTrackAngle_H

#include "RecoLocalTracker/SiStripRecHitConverter/interface/StripCPE.h"

class StripCPEfromTrackAngle : public StripCPE 
{

 public:
  using StripCPE::localParameters;
  
  //Error parameterization, low cluster width function
  float LC_P[3];
  float HC_P[4][2];

  //High cluster width is broken down by sub-det
  std::map<SiStripDetId::SubDetector, float> HC_P0;
  std::map<SiStripDetId::SubDetector, float> HC_P1;
  
  StripClusterParameterEstimator::LocalValues
  localParameters( const SiStripCluster&, const GeomDetUnit&, const LocalTrajectoryParameters&) const;
  
  float stripErrorSquared(const unsigned N, const float uProj, const SiStripDetId::SubDetector loc ) const ;

  StripCPEfromTrackAngle( edm::ParameterSet & conf, 
			  const MagneticField& mag, 
			  const TrackerGeometry& geom, 
			  const SiStripLorentzAngle& lorentz,
                          const SiStripBackPlaneCorrection& backPlaneCorrection,
			  const SiStripConfObject& confObj,
			  const SiStripLatency& latency) 
  : StripCPE(conf, mag, geom, lorentz, backPlaneCorrection, confObj, latency )
  {
    LC_P[0] = conf.existsAs<double>("LC_P0") ? conf.getParameter<double>("LC_P0") : -.326;
    LC_P[1] = conf.existsAs<double>("LC_P1") ? conf.getParameter<double>("LC_P1") :  .618;
    LC_P[2] = conf.existsAs<double>("LC_P2") ? conf.getParameter<double>("LC_P2") :  .300;

    HC_P[SiStripDetId::TIB - 3][0] = conf.existsAs<double>("TIB_P0") ? conf.getParameter<double>("TIB_P0") : -.742  ;
    HC_P[SiStripDetId::TIB - 3][1] = conf.existsAs<double>("TIB_P1") ? conf.getParameter<double>("TIB_P1") :  .202  ;
    HC_P[SiStripDetId::TID - 3][0] = conf.existsAs<double>("TID_P0") ? conf.getParameter<double>("TID_P0") : -1.026 ;
    HC_P[SiStripDetId::TID - 3][1] = conf.existsAs<double>("TID_P1") ? conf.getParameter<double>("TID_P1") :  .253  ;
    HC_P[SiStripDetId::TOB - 3][0] = conf.existsAs<double>("TOB_P0") ? conf.getParameter<double>("TOB_P0") : -1.427 ;
    HC_P[SiStripDetId::TOB - 3][1] = conf.existsAs<double>("TOB_P1") ? conf.getParameter<double>("TOB_P1") :  .433  ;
    HC_P[SiStripDetId::TEC - 3][0] = conf.existsAs<double>("TEC_P0") ? conf.getParameter<double>("TEC_P0") : -1.885 ;
    HC_P[SiStripDetId::TEC - 3][1] = conf.existsAs<double>("TEC_P1") ? conf.getParameter<double>("TEC_P1") :  .471  ;  
  }
};
#endif
