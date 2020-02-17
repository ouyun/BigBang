// Copyright (c) 2019-2020 The Bigbang developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "delegateverify.h"

using namespace std;
using namespace xengine;

namespace bigbang
{
namespace delegate
{

//////////////////////////////
// CDelegateVerify

CDelegateVerify::CDelegateVerify(const map<CDestination, size_t>& mapWeight,
                                 const map<CDestination, vector<unsigned char>>& mapEnrollData)
{
    Enroll(mapWeight, mapEnrollData);
}

bool CDelegateVerify::VerifyProof(const vector<unsigned char>& vchProof, uint256& nAgreement,
                                  size_t& nWeight, map<CDestination, size_t>& mapBallot)
{
    uint256 nAgreementParse;
    try
    {
        unsigned char nWeightParse;
        vector<CDelegateData> vPublish;
        CIDataStream is(vchProof);
        is >> nWeightParse >> nAgreementParse;
        if (nWeightParse == 0 && nAgreementParse == 0)
        {
            return true;
        }
        is >> vPublish;
        bool fCompleted = false;
        for (int i = 0; i < vPublish.size(); i++)
        {
            const CDelegateData& delegateData = vPublish[i];
            if (!VerifySignature(delegateData)
                || !witness.Collect(delegateData.nIdentFrom, delegateData.mapShare, fCompleted))
            {
                xengine::StdTrace("CDelegateVerify", "VerifyProof fail point 1");
                return false;
            }
        }
    }
    catch (exception& e)
    {
        StdError(__PRETTY_FUNCTION__, e.what());
        xengine::StdTrace("CDelegateVerify", "VerifyProof fail point 2: %s", e.what());
        return false;
    }

    GetAgreement(nAgreement, nWeight, mapBallot);
    xengine::StdTrace("CDelegateVerify", "VerifyProof point 3: nAgreement[%s] vs. nAgreementParse[%s]",
                      nAgreement.ToString().c_str(), nAgreementParse.ToString().c_str());

    return (nAgreement == nAgreementParse);
}

} // namespace delegate
} // namespace bigbang
