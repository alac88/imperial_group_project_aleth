const HoneyPot = artifacts.require("HoneyPot");
const HoneyPotCollect = artifacts.require("HoneyPotCollect");
const LockedEther = artifacts.require("LockedEther");
const Library = artifacts.require("Library");

module.exports = function(deployer) {
  // deployer.deploy(LockedEther);
  // deployer.deploy(Library);
  // deployer.deploy(HoneyPot);
  deployer.deploy(HoneyPotCollect);
};
