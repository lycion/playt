// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The PlayT developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        //(0, uint256("0x000002b741bab69832a04d07f9aae1db7a6243c950cd2ba2ef2adf14d2b10949"))
        (0, uint256("000007d1c0c2dbc8c5b0dea48347863fc62aec25ef97eeffffd62fe33189f3c0"))        
        ;

static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        //1471809614, // * UNIX timestamp of last checkpoint block
        //1998064,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        //2800        // * estimated number of transactions per day after checkpoint
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 261, uint256("0x"))
        ;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        //1405699509,
        //201,
        //500
    };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0x000008ca1832a4baf228eb1553c03d3a2c8e02399550dd6ea8d65cec3ef23d2e"))
        ;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xd1;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0xd4;        
        //vAlertPubKey = ParseHex("0466b6916465661ad39d2bc298058b9229fc34e50b87532bbf580c282bcba78b2e8b8d99897121e2fef51c2274bb57fffc172fab75171d2ca82c91feaf60efe1e0");
        vAlertPubKey = ParseHex("MHQCAQEEIMzf9ZZIMXSkrUPHkRqmJhn/7tXT6HASszo7HWlE0asfoAcGBSuBBAAKoUQDQgAERt8+9orN51nuZ8vTCSsEcv3fmO9hmw5/BUBiboIohbK+SG7JuKvNoYf1mjs7rhFoh3vAnZ0YvDOfO+X3hopgQQ");

        nDefaultPort = 8889;
        //org
        bnProofOfWorkLimit = ~uint256(0) >> 20;  // PlayT starting difficulty is 1 / 2^12
        //new
        //bnProofOfWorkLimit = ~uint256(0) >> 10;  // PlayT starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 24 * 60 * 60; // PlayT: 1 day
        nTargetSpacing = 10 * 60; // PlayT: 10 minutes");

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */

        const char* pszTimestamp = "main playt 1536905745";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        //txNew.vout[0].scriptPubKey = CScript() << ParseHex("040f084712e3c7cb08a5086e49ef8627c801f1e2d42325a4a0274f98bca6d4a773769c8f1d4c9e1f993f7ad4d75aa2fc24b72a6365715b88746b8f41870e4ca192") << OP_CHECKSIG;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("MHQCAQEEIGVxGHhGfiQteYZO/mvigAoBiiqfPCF4x5r05qdERrFboAcGBSuBBAAKoUQDQgAEOr8apiAcjwhM8ObJjYEmJHWRpEPNJZnh22xnaMAA2s0fe1zt0m8p4KIKNx3uKlVQIKCb/UMAAR4tdAKm2GIFpg") << OP_CHECKSIG;

        

        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        //genesis.nTime    = 1524473665;
        //genesis.nBits    = 0x1e0ffff0;
        //genesis.nNonce   = 124737539;
        //genesis.nTime    = 1526289408;
        genesis.nTime    = 1536905745;
        genesis.nBits    = 0x1e0ffff0;        
        genesis.nNonce   = 504514;


        //hashGenesisBlock = genesis.GetHash();

        ///*        
        hashGenesisBlock = uint256("0x01");
        if (false && genesis.GetHash() != hashGenesisBlock)
        {
            printf("main net \n");
            printf("recalculating params for mainnet.\n");
            printf("old mainnet genesis nonce: %d\n", genesis.nNonce);
            printf("old mainnet genesis hash:  %s\n", hashGenesisBlock.ToString().c_str());
            // deliberately empty for loop finds nonce value.
            for(genesis.nNonce = 0; genesis.GetHash() > bnProofOfWorkLimit; genesis.nNonce++)
            {
              //printf("genesis.nNounce : %d \n", genesis.nNonce);
            }
            printf("new mainnet genesis hash: %s\n", genesis.GetHash().ToString().c_str());            
            printf("new mainnet genesis nonce: %d\n", genesis.nNonce);
            printf("new mainnet genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        }
        //*/

        hashGenesisBlock = genesis.GetHash();        
        assert(hashGenesisBlock == uint256("000007d1c0c2dbc8c5b0dea48347863fc62aec25ef97eeffffd62fe33189f3c0"));
        assert(genesis.hashMerkleRoot == uint256("a0e67e66ddb0a5f861daa417f58ee8b2703b0e830cacba41bce80f6fac776a9c"));
        
        //vSeeds.push_back(CDNSSeedData("220.85.13.236", "220.85.13.236"));
        //vSeeds.push_back(CDNSSeedData("192.168.0.44", "192.168.0.44"));
        vSeeds.push_back(CDNSSeedData("211.196.150.249", "211.196.150.249"));
        vSeeds.push_back(CDNSSeedData("211.196.150.248", "211.196.150.248"));
        vSeeds.push_back(CDNSSeedData("211.196.150.250", "211.196.150.250"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of( 76);                    // PlayT addresses start with 'X'
        base58Prefixes[SCRIPT_ADDRESS] = list_of( 16);                    // PlayT script addresses start with '7'
        base58Prefixes[SECRET_KEY] =     list_of(204);                    // PlayT private keys start with '7' or 'X'
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x02)(0xFE)(0x52)(0xF8); // PlayT BIP32 pubkeys start with 'drkv'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x02)(0xFE)(0x52)(0xCC); // PlayT BIP32 prvkeys start with 'drkp'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000005);             // PlayT BIP44 coin type is '5'

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        //vFixedSeeds.clear();
        //vSeeds.clear();

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04549ac134f694c0243f503e8c8a9a986f5de6610049c40b07816809b0d1d06a21b07be27b9bb555931773f62ba6cf35a25fd52f694d4e1106ccd237a7bb899fdd";
        strMasternodePaymentsPubKey = "04549ac134f694c0243f503e8c8a9a986f5de6610049c40b07816809b0d1d06a21b07be27b9bb555931773f62ba6cf35a25fd52f694d4e1106ccd237a7bb899fdd";
        strDarksendPoolDummyAddress = "Xq19GqFvajRrEdDHYRKGYjTsQfpV5jyipF";
        nStartMasternodePayments = 1403728576; //Wed, 25 Jun 2014 20:36:16 GMT
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test playt 1536905909";
        pchMessageStart[0] = 0xd1;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0xa4;
        pchMessageStart[3] = 0xdc;
        //vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");

        //04:57:63:cf:f7:c9:d7:07:13:6c:31:47:84:25:a9:5a:70:bb:d1:41:5e:96:62:3a:8d:3d:13:7a:d6:ce:1c:8d:06:0c:db:b7:2c:49:fa:a0:2d:a9:62:76:4b:05:55:5c:d2:05:7a:92:09:58:be:e7:3d:df:a2:18:5f:0d:bc:0b:9c
        //vAlertPubKey = ParseHex("04faa632781a7673b5c7057419bbf5263d474663cbc28f37682d6775f5d4e56d05ce68e5b385a57b042e5a02b15bba922c3e7217ebf199e0583ac3760b444243ba");
        vAlertPubKey = ParseHex("MHQCAQEEIGVxGHhGfiQteYZO/mvigAoBiiqfPCF4x5r05qdERrFboAcGBSuBBAAKoUQDQgAEOr8apiAcjwhM8ObJjYEmJHWRpEPNJZnh22xnaMAA2s0fe1zt0m8p4KIKNx3uKlVQIKCb/UMAAR4tdAKm2GIFpg");


        nDefaultPort = 18889;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 24 * 60 * 60; // PlayT: 1 day
        nTargetSpacing = 10 * 60; // PlayT: 10 minutes");

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        //genesis.nTime = 1526289408;
        genesis.nTime    = 1536905909;
        //genesis.nBits = 0x1e0ffff0;
        //genesis.nNonce = 124737539;
        genesis.nNonce = 334874;

        ///*        
        if (false && genesis.GetHash() != hashGenesisBlock)
        {
            printf("test net \n");
            printf("recalculating params for mainnet.\n");
            printf("old mainnet genesis nonce: %d\n", genesis.nNonce);
            printf("old mainnet genesis hash:  %s\n", hashGenesisBlock.ToString().c_str());
            // deliberately empty for loop finds nonce value.
            for(genesis.nNonce = 0; genesis.GetHash() > bnProofOfWorkLimit; genesis.nNonce++)
            {
              //printf("genesis.nNounce : %d \n", genesis.nNonce);
            }
            printf("new mainnet genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString().c_str());
            printf("new mainnet genesis nonce: %d\n", genesis.nNonce);
            printf("new mainnet genesis hash: %s\n", genesis.GetHash().ToString().c_str());
        }
        //*/

        hashGenesisBlock = genesis.GetHash();        
        assert(hashGenesisBlock == uint256("000009124dd7b70067c7d76f7393101708b0e54c6e901bf388a1be7cf1deaf5a"));        

        vFixedSeeds.clear();
        vSeeds.clear();
        /*vSeeds.push_back(CDNSSeedData("playtpay.io", "testnet-seed.playtpay.io"));
        vSeeds.push_back(CDNSSeedData("playt.qa", "testnet-seed.playt.qa"));
        *///legacy seeders

        //vSeeds.push_back(CDNSSeedData("darkcoin.io",  "testnet-seed.darkcoin.io"));
        //vSeeds.push_back(CDNSSeedData("darkcoin.qa", "testnet-seed.darkcoin.qa"));
        //vSeeds.push_back(CDNSSeedData("masternode.io", "test.dnsseed.masternode.io"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(139);                    // Testnet playt addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = list_of( 19);                    // Testnet playt script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY]     = list_of(239);                    // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x3a)(0x80)(0x61)(0xa0); // Testnet playt BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x3a)(0x80)(0x58)(0x37); // Testnet playt BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000001);             // Testnet playt BIP44 coin type is '5' (All coin's testnet default)

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        strMasternodePaymentsPubKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        strDarksendPoolDummyAddress = "y1EZuxhhNMAUofTBEeLqGE1bJrpC2TWRNp";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test2
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "test";
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xdc;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // PlayT: 1 day        
        nTargetSpacing = 10 * 60; // PlayT: 10 minutes");
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        //genesis.nTime = 1526289408;
        genesis.nTime    = 1536906297;
        genesis.nBits = 0x1e0ffff0;
        //genesis.nNonce = 124737539;
        genesis.nNonce = 1;

        ///*        
        if (false && genesis.GetHash() != hashGenesisBlock)
        {
            printf("reg test net\n");
            printf("recalculating params for mainnet.\n");
            printf("old mainnet genesis nonce: %d\n", genesis.nNonce);
            printf("old mainnet genesis hash:  %s\n", hashGenesisBlock.ToString().c_str());
            // deliberately empty for loop finds nonce value.
            for(genesis.nNonce = 0; genesis.GetHash() > bnProofOfWorkLimit; genesis.nNonce++)
            {
              //printf("genesis.nNounce : %d \n", genesis.nNonce);
            }
            printf("new mainnet genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString().c_str());
            printf("new mainnet genesis nonce: %d\n", genesis.nNonce);
            printf("new mainnet genesis hash: %s\n", genesis.GetHash().ToString().c_str());
        }
        //*/

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 19994;        
        assert(hashGenesisBlock == uint256("3fa1ea7144a94a3e5ebcad17a44692dac829ff7afd9b5a5765039875937e03c5"));
        

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
