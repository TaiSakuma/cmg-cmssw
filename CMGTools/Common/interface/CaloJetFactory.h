#ifndef _CMGTools_Common_CaloJetFactory_h_
#define _CMGTools_Common_CaloJetFactory_h_

//____________________________________________________________________________||
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "AnalysisDataFormats/CMGTools/interface/CaloJet.h"
#include "CMGTools/Common/interface/Factory.h"
#include "CMGTools/Common/interface/BaseJetFactory.h"

#include <iostream>
#include <memory>

//____________________________________________________________________________||
namespace cmg
{

class CaloJetFactory : public Factory<cmg::CaloJet>{
  public:
    CaloJetFactory(const edm::ParameterSet& ps);

    virtual event_ptr create(const edm::Event&, const edm::EventSetup&);

    void setPFproperties(const pat::Jet&, cmg::CaloJet*, bool) const;

  private:
    const edm::InputTag jetLabel_;
    const BaseJetFactory baseJetFactory_;

  };

}

//____________________________________________________________________________||
#endif /*_CMGTools_Common_CaloJetFactory_h_*/
