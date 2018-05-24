var Web3 = require('web3');
var web3 = new Web3();
web3.setProvider(new web3.providers.HttpProvider());

// Query initial values
var me = web3.eth.coinbase;
var originalBalance = web3.eth.getBalance(me).toNumber();
var blocks = web3.eth.blockNumber;
var lastBlock = web3.eth.getBlock(blocks);
var blocksMined = 0; 

// Ethereum blockchain
document.getElementById('coinbase').innerText = 'Me: ' + me;
document.getElementById('original').innerText = ' Original Eth: ' + web3.fromWei(originalBalance) + '    watching...';
document.getElementById('blocks').innerText = ' Blocks: ' +  blocks;  
document.getElementById('totaldifficulty').innerText = 'Total Difficulty: ' + lastBlock.totalDifficulty; 

// Node value
if (web3.eth.mining === true) {
  // Thinking
  document.getElementById('state').style.backgroundColor = "green";  
} else {
  document.getElementById('state').style.backgroundColor = "red"; 
}

// Last block values
document.getElementById('number').innerText = 'Number: ' + lastBlock.number; 
document.getElementById('hash').innerText = 'Hash: ' + lastBlock.hash; 
document.getElementById('difficulty').innerText = 'Difficulty: ' + lastBlock.difficulty; 
document.getElementById('miner').innerText = 'Miner: ' + lastBlock.miner; 

function watchBalance() {
    web3.eth.filter('latest').watch(function() {
        var currentBalance = web3.eth.getBalance(me).toNumber();
        blocks = web3.eth.blockNumber;
        lastBlock = web3.eth.getBlock(blocks);

        // Ethereum Blockchain
        document.getElementById("current").innerText = 'Current Eth: ' + web3.fromWei(currentBalance);
        document.getElementById('blocks').innerText = ' Blocks: ' +  blocks; 
        document.getElementById('difficulty').innerText = ' Difficulty: ' +  difficulty; 
        document.getElementById('totaldifficulty').innerText = 'Total Difficulty: ' + lastBlock.totalDifficulty; 

        // Node value
        if (web3.eth.mining === true) {
          // Mining.
          document.getElementById('state').style.backgroundColor = "green";  
        } else {
          // Not-mining. 
          document.getElementById('state').style.backgroundColor = "red"; 
        }

        // Calculate the number of blocks mined by this node. 
        if (lastBlock.miner === me) {
          blocksMined += 1; 
        }
        document.getElementById('numBlocks').innerText = blocksMined;

        // New block values
        document.getElementById('number').innerText = 'Number: ' + lastBlock.number; 
        document.getElementById('hash').innerText = 'Hash: ' + lastBlock.hash; 
        document.getElementById('difficulty').innerText = 'Difficulty: ' + lastBlock.difficulty; 
        document.getElementById('miner').innerText = 'Miner: ' + lastBlock.miner; 
    });
}

function startMining() {
  web3.eth.mining.start();
}

watchBalance();