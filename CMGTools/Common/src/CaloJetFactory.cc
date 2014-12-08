
//____________________________________________________________________________||
#include "CMGTools/Common/interface/CaloJetFactory.h"
#include "DataFormats/Common/interface/ValueMap.h"

#include <iostream>

//____________________________________________________________________________||
cmg::CaloJetFactory::CaloJetFactory(const edm::ParameterSet& ps)
  : jetLabel_(ps.getParameter<edm::InputTag>("inputCollection"))
  , baseJetFactory_(ps.getParameter<edm::ParameterSet>("baseJetFactory"))
{
  std::cout<<"jet collection in the CaloJetFactory = " << jetLabel_ << std::endl;
}

//____________________________________________________________________________||
cmg::CaloJetFactory::event_ptr cmg::CaloJetFactory::create(const edm::Event& iEvent, const edm::EventSetup&)
{

  edm::Handle<pat::JetCollection> jetCands;

  cmg::CaloJetFactory::event_ptr result(new cmg::CaloJetFactory::collection);
  iEvent.getByLabel(jetLabel_, jetCands);

  for(pat::JetCollection::size_type i = 0; i != jetCands->size(); ++i)
    {
      pat::JetPtr jetPtr(jetCands, i);
      cmg::CaloJet cmgjet(jetPtr);
      baseJetFactory_.set(jetPtr, &cmgjet);
      result->push_back(cmgjet);
    }

  return result;
}

//____________________________________________________________________________||
