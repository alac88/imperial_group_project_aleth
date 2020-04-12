// Simple - Re-entrancy
const HoneyPot = artifacts.require("HoneyPot");
const HoneyPotCollect = artifacts.require("HoneyPotCollect");

// Simple - Locker Ether
const LockedEther = artifacts.require("LockedEther");
const Library = artifacts.require("Library");

// Simple - Unhandled exception
const UnhandledException = artifacts.require("UnhandledException");

// Spanked


// Parity bug - Locked Ether
const TestParity = artifacts.require("TestParity");
const Wallet = artifacts.require("Wallet");
const WalletEvents = artifacts.require("WalletEvents");
const WalletLibrary = artifacts.require("WalletLibrary");

// DAO Attack - Re-entrancy
const Dao = artifacts.require("Dao");
const DaoAttacker = artifacts.require("DaoAttacker");

// ???
// const StandardToken = artifacts.require("StandardToken");
// const HumanStandardToken = artifacts.require("HumanStandardToken");
// const LedgerChannel = artifacts.require("LedgerChannel");


module.exports = function(deployer) {
  // deployer.deploy(HoneyPot);
  // deployer.deploy(HoneyPotCollect);
  
  // deployer.deploy(LockedEther);
  // deployer.deploy(Library);
  
  // deployer.deploy(UnhandledException);

  // deployer.deploy(TestParity);
  // deployer.deploy(Wallet, ["0x01bd4ccabe2d59ec09115918ab389a2c0fd3677d"], 1, 1);
  // deployer.deploy(WalletEvents);
  // deployer.deploy(WalletLibrary);
  
  // deployer.deploy(Dao);
  deployer.deploy(DaoAttacker);
  
  // deployer.deploy(StandardToken);
  // deployer.deploy(HumanStandardToken);
  // deployer.deploy(LedgerChannel);
};
