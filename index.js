var Web3 = require('web3');
var web3 = new Web3();

// Total peers.
const peers = ["http://localhost:8545", "http://localhost:8544"];
var blocksMinedNode1 = calcMinedBlocks(peers[0]);
var blocksMinedNode2 = calcMinedBlocks(peers[1]);

// Set a web3 provider based on the ip addresses of the peers. 
setWeb3Provider(); 

// General blockchain values. 
printBlockchain(); 

// Node 1 values.
printNode1(); 

// Node 2 values. 
printNode2();

// Last block values. 
printLastBlock(); 

function watchForUpdates() {
  var node1 = new Web3(); 
  node1.setProvider(new node1.providers.HttpProvider(peers[0])); 
  if (!node1.isConnected()) {
    console.error("Can't connect to geth for Node 0");
    return;
  }

  node1.eth.filter('latest').watch(function(error, result) {
    if (!error) {
        // Get last block. 
        var lastBlock = node1.eth.getBlock(node1.eth.blockNumber);
        var coinbase = node1.eth.coinbase;
        if (lastBlock.miner === coinbase) {
          blocksMinedNode1++; // New block mined with 0
        }

        // Update node1 values. 
        printNode1();
        printLastBlock();
        printBlockchain();
    }
  });

  var node2 = new Web3(); 
  node2.setProvider(new node2.providers.HttpProvider(peers[1])); 
  if (!node2.isConnected()) {
    console.error("Can't connect to geth for Node 1");
    return;
  }

  node2.eth.filter('latest').watch(function(error, result) {
    if (!error) {
        // Get last block. 
        var lastBlock = node2.eth.getBlock(node2.eth.blockNumber);
        var coinbase = node2.eth.coinbase;
        if (lastBlock.miner === coinbase) {
          blocksMinedNode2++; // New block mined with 0
        }

        // Update node1 values. 
        printNode2();
        printLastBlock();
        printBlockchain();
    }
  });
}

// [TODO] Defer this call since it's a computationally expensive call.
function calcMinedBlocks() {
  // argument[0] receives the peer string. 
  var peer = arguments[0];

  // Connect to web3 for this peer. 
  web3.setProvider(new web3.providers.HttpProvider(peer));

  // Check if it's a valid web3 connection. 
  if (!web3.isConnected()) {
    console.error("No connection found with geth. Start geth on the nodes.");
    return; 
  }

  // Go through all the blocks and check which blocks were mined by this node.  
  var blocks = web3.eth.blockNumber; 
  var coinbase = web3.eth.coinbase; 
  var numBlocksMined = 0; 
  for (var i = 0; i < blocks; i++) {
    var block = web3.eth.getBlock(i);
    if (block.miner === coinbase) {
      numBlocksMined++;
    }
  }

  return numBlocksMined; 
}

function setWeb3Provider() {
  var isConnected = false; 
  // Find a web3 connection that's connected. 
  for (var i = 0; i < peers.length; i++) {
    web3.setProvider(new web3.providers.HttpProvider(peers[i]));
    if (web3.isConnected()) {
      isConnected = true; 
      break;
    }
  }

  // No connection found with geth. 
  if (isConnected === false) {
    document.getElementById('connection').style.backgroundColor = "red";
    console.error("No connection found with geth. Start geth on the nodes.");
    return;
  } else {
    console.log("Geth Connection successful."); 
    document.getElementById('connection').style.backgroundColor = "green";
  }
}

function printBlockchain() {
  // These are common Ethereum blockchain values. 
  var blocks = web3.eth.blockNumber - 1; // First block is the genesis block
  var lastBlock = web3.eth.getBlock(blocks);
  document.getElementById('blocks').innerText = ' Blocks: ' +  blocks;  
  document.getElementById('totaldifficulty').innerText = 'Total Difficulty: ' + lastBlock.totalDifficulty;
}

function printNode1() {
  // Set the provider for 1st node. 
  web3.setProvider(new web3.providers.HttpProvider(peers[0]));
  if (!web3.isConnected()) {
    console.error("Unable to connect to Node 1 geth instance.");
    return; 
  }

  // Mining state. 
  web3.eth.mining ? document.getElementById('node1').style.backgroundColor = "green" : document.getElementById('node1').style.backgroundColor = "red"; 

  // Coinbase address
  var me = web3.eth.coinbase; 
  document.getElementById('address1').innerText = 'Coinbase: ' + me;

  // Account balance. 
  var balance = web3.eth.getBalance(me).toNumber();
  document.getElementById('balance1').innerText = 'Balance: ' + web3.fromWei(balance);

  // Current blocks
  document.getElementById('numBlocks1').innerText = blocksMinedNode1; 
}

function printNode2() {
    // Set the provider for 1st node. 
    web3.setProvider(new web3.providers.HttpProvider(peers[1]));
    if (!web3.isConnected()) {
      console.error("Unable to connect to Node 1 geth instance.");
      return; 
    }
  
    // Mining state. 
    web3.eth.mining ? document.getElementById('node2').style.backgroundColor = "green" : document.getElementById('node2').style.backgroundColor = "red"; 
  
    // Coinbase address
    var me = web3.eth.coinbase; 
    document.getElementById('address2').innerText = 'Coinbase: ' + me;
  
    // Account balance. 
    var balance = web3.eth.getBalance(me).toNumber();
    document.getElementById('balance2').innerText = 'Balance: ' + web3.fromWei(balance);
  
    // Blocks mined. 
    document.getElementById('numBlocks2').innerText = blocksMinedNode2; 
}

function printLastBlock() {
  var lastBlock = web3.eth.getBlock(web3.eth.blockNumber);

  // New block values
  document.getElementById('number').innerText = 'Number: ' + lastBlock.number; 
  document.getElementById('hash').innerText = 'Hash: ' + lastBlock.hash; 
  document.getElementById('difficulty').innerText = 'Difficulty: ' + lastBlock.difficulty; 
  document.getElementById('miner').innerText = 'Miner: ' + lastBlock.miner; 
}

watchForUpdates();
