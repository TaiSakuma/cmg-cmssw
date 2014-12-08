#ifndef _AnalysisDataFormats_CMGTools_CaloJet_H_
#define _AnalysisDataFormats_CMGTools_CaloJet_H_

//____________________________________________________________________________||
#include "AnalysisDataFormats/CMGTools/interface/BaseJet.h"

//____________________________________________________________________________||
namespace cmg {

  /** Class representing CaloJets in the CMG framework.

  In the current implementation, this class does not add anything
  significant to its base class. In the viewpoint of the
  functionality, this class is needless. This class lets BaseJet be a
  base class as its name indicates. It also places CaloJet and PFJet
  in the same depth of the class hierarchy tree.

  (Alternatively, this class could be implemented as a typedef of
  BaseJet until a content is added.)

  */

  class CaloJet : public BaseJet
  {
  public:

    CaloJet() {}
    CaloJet(const value& m) : BaseJet(m) {}
    virtual ~CaloJet(){}

    friend class CaloJetFactory;

  private:

};

} // namespace cmg

//____________________________________________________________________________||
#endif // _AnalysisDataFormats_CMGTools_CaloJet_H_
