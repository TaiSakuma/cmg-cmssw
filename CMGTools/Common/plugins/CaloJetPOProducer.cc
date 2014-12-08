#include "CMGTools/Common/plugins/PhysicsObjectProducer.h"
#include "CMGTools/Common/interface/CaloJetFactory.h"

#include "FWCore/Framework/interface/MakerMacros.h"

typedef PhysicsObjectProducer<cmg::CaloJetFactory> CaloJetPOProducer;
DEFINE_FWK_MODULE(CaloJetPOProducer);
