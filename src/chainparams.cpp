// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"
#include "consensus/consensus.h"
#include "zerocoin_params.h"
#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "libzerocoin/bitcoin_bignum/bignum.h"
#include <assert.h>
#include <boost/assign/list_of.hpp>
#include "chainparamsseeds.h"
#include "arith_uint256.h"

static CBlock CreateGenesisBlock(const char *pszTimestamp, const CScript &genesisOutputScript, uint32_t nTime, uint32_t nNonce,
                   uint32_t nBits, int32_t nVersion, const CAmount &genesisReward,
                   std::vector<unsigned char> extraNonce)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 0x1f0fffff << CBigNum(4).getvch() << std::vector < unsigned
    char >
    ((const unsigned char *) pszTimestamp, (const unsigned char *) pszTimestamp + strlen(pszTimestamp)) << extraNonce;
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime = nTime;
    genesis.nBits = nBits;
    genesis.nNonce = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount &genesisReward, std::vector<unsigned char> extraNonce)
{
    const char *pszTimestamp = "Lets Swap Hexx";
    const CScript genesisOutputScript = CScript();
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward, extraNonce);
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        strNetworkID = "main";
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 150; // every block
        consensus.nPowTargetSpacing = 150; // 2.5 minute blocks
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
		consensus.nRuleChangeActivationThreshold = 1900; // 95% of 100
        consensus.nMinerConfirmationWindow = 2000;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1462060800; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1479168000; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1517744282; //
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517744282; // 

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1517744282; //
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1517744282; // 

        // bznode params
        strSporkPubKey = "04ffde6668d0dff8ba92c67b1f751568e11608f23c8c0437eccd5a6ec713ae3638238478b816783593d552bc8b6a57147dd67596eb372b0cadc743d3835c43e9e3";
        strBznodePaymentsPubKey = "04ffde6668d0dff8ba92c67b1f751568e11608f23c8c0437eccd5a6ec713ae3638238478b816783593d552bc8b6a57147dd67596eb372b0cadc743d3835c43e9e3";

        pchMessageStart[0] = { 'b' };
        pchMessageStart[1] = { 'z' };
        pchMessageStart[2] = { 'x' };
        pchMessageStart[3] = { '0' };
        nDefaultPort = 29301;
        nPruneAfterHeight = 100000;
        std::vector<unsigned char> extraNonce(4);
		extraNonce[0] = 0x82;
		extraNonce[1] = 0x3f;
		extraNonce[2] = 0x00;
		extraNonce[3] = 0x00;
        genesis = CreateGenesisBlock(1485785935, 2610, 0x1f0fffff, 2, 0 * COIN, extraNonce);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x322bad477efb4b33fa4b1f0b2861eaf543c61068da9898a95062fdb02ada486f"));
        assert(genesis.hashMerkleRoot == uint256S("0x31f49b23f8a1185f85a6a6972446e72a86d50ca0e3b3ffe217d0c2fea30473db"));
        vSeeds.push_back(CDNSSeedData("54.38.187.24", "54.38.187.24"));
        vSeeds.push_back(CDNSSeedData("185.64.20.193", "185.64.20.193"));
        vSeeds.push_back(CDNSSeedData("185.64.20.194", "185.64.20.194"));
        vSeeds.push_back(CDNSSeedData("185.64.20.195", "185.64.20.195"));
        vSeeds.push_back(CDNSSeedData("185.64.20.196", "185.64.20.196"));
        vSeeds.push_back(CDNSSeedData("185.64.20.201", "185.64.20.201"));
        vSeeds.push_back(CDNSSeedData("185.64.20.202", "185.64.20.202"));
        vSeeds.push_back(CDNSSeedData("185.64.20.203", "185.64.20.203"));
        vSeeds.push_back(CDNSSeedData("185.64.20.204", "185.64.20.204"));
        vSeeds.push_back(CDNSSeedData("5.79.119.106", "5.79.119.106"));
        vSeeds.push_back(CDNSSeedData("76.74.170.128", "76.74.170.128"));
        vSeeds.push_back(CDNSSeedData("81.171.19.63", "81.171.19.63"));
        vSeeds.push_back(CDNSSeedData("81.171.29.144", "81.171.29.144"));
        vSeeds.push_back(CDNSSeedData("95.211.244.14", "95.211.244.14"));
        vSeeds.push_back(CDNSSeedData("81.17.60.209", "81.17.60.209"));
        vSeeds.push_back(CDNSSeedData("81.17.60.210", "81.17.60.210"));
        vSeeds.push_back(CDNSSeedData("81.17.60.211", "81.17.60.211"));
        vSeeds.push_back(CDNSSeedData("5.79.70.22", "5.79.70.22"));
        vSeeds.push_back(CDNSSeedData("62.212.95.122", "62.212.95.122"));
        vSeeds.push_back(CDNSSeedData("37.48.115.170", "37.48.115.170"));
        vSeeds.push_back(CDNSSeedData("81.171.29.52", "81.171.29.52"));
        vSeeds.push_back(CDNSSeedData("5.79.106.46", "5.79.106.46"));
        vSeeds.push_back(CDNSSeedData("5.79.100.69", "5.79.100.69"));
        vSeeds.push_back(CDNSSeedData("5.79.113.83", "5.79.113.83"));
        vSeeds.push_back(CDNSSeedData("5.79.109.42", "5.79.109.42"));
        vSeeds.push_back(CDNSSeedData("81.171.12.116", "81.171.12.116"));
        vSeeds.push_back(CDNSSeedData("5.79.119.152", "5.79.119.152"));
        vSeeds.push_back(CDNSSeedData("5.79.119.153", "5.79.119.153"));
        vSeeds.push_back(CDNSSeedData("37.48.73.102", "37.48.73.102"));
        vSeeds.push_back(CDNSSeedData("37.48.90.244", "37.48.90.244"));
        vSeeds.push_back(CDNSSeedData("5.79.119.228", "5.79.119.228"));
        vSeeds.push_back(CDNSSeedData("37.48.73.245", "37.48.73.245"));
        vSeeds.push_back(CDNSSeedData("37.48.73.232", "37.48.73.232"));
        vSeeds.push_back(CDNSSeedData("95.211.247.232", "95.211.247.232"));
        base58Prefixes[PUBKEY_ADDRESS] = std::vector < unsigned char > (1, 75);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector < unsigned char > (1, 34);
        base58Prefixes[SECRET_KEY] = std::vector < unsigned char > (1, 210);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container < std::vector < unsigned char > > ();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container < std::vector < unsigned char > > ();
        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData)
		{
		boost::assign::map_list_of
        (    0, uint256S("0x322bad477efb4b33fa4b1f0b2861eaf543c61068da9898a95062fdb02ada486f"))
        (    1, uint256S("0x639d4e6db07825e29b299930ceb2b3bf90e033cb3b3d05dc9db036afca084aed"))
        (   14, uint256S("0xffdd4dc36744a881e31d3cf7c0800631927ed3c3a358ead79db0e7cf78961f85"))
        ( 4952, uint256S("0x080f7e0c158cef7cbca330625e2132af88cf296191b19bea9d374aef542523dd"))
        ( 7155, uint256S("0x613b2da5049f7b0b19f3af636ddbd58c687e7e08720c78026937d88818a399d3"))
        (11175, uint256S("0x84445b39ce4e0510f1479daa842a909850436c5ab82b8958d4148ca0f7b97771"))
		(26136, uint256S("0xe4b2de4bfad0472351fbbdfc23246dd204bd04ee2ba3eac078edf703939b6e3d"))
		(35000, uint256S("064014305617e963754efeee752c5cfc5e5eb0b1d104c690cf35e38c436af0dd3")),
        1541007233, // * UNIX timestamp of last checkpoint block
        1000000,    // * total number of transactions between genesis and last checkpoint
                  //   (the tx=... number in the SetBestChain debug.log lines)
		576.0 // * estimated number of transactions per day after checkpoint
		};

        nCheckBugFixedAtBlock = ZC_CHECK_BUG_FIXED_AT_BLOCK;
        nSpendV15StartBlock = ZC_V1_5_STARTING_BLOCK;
        nSpendV2ID_1 = ZC_V2_SWITCH_ID_1;
        nSpendV2ID_10 = ZC_V2_SWITCH_ID_10;
        nSpendV2ID_25 = ZC_V2_SWITCH_ID_25;
        nSpendV2ID_50 = ZC_V2_SWITCH_ID_50;
        nSpendV2ID_100 = ZC_V2_SWITCH_ID_100;
        nModulusV2StartBlock = ZC_MODULUS_V2_START_BLOCK;
        nModulusV1MempoolStopBlock = ZC_MODULUS_V1_MEMPOOL_STOP_BLOCK;
        nModulusV1StopBlock = ZC_MODULUS_V1_STOP_BLOCK;

	}
};

static CMainParams mainParams;

/**
 * Testnet
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams()
	{
        strNetworkID = "test";
    }
};

static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams()
	{
        strNetworkID = "regtest";
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
	{
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};

static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(const std::string &chain) {
    if (chain == CBaseChainParams::MAIN)
        return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
        return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
        return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string &network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout) {
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}
