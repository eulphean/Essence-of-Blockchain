var Web3 = require('web3');
var web3 = new Web3();
web3.setProvider(new web3.providers.HttpProvider());

function watchBalance() {
    var coinbase = web3.eth.coinbase;
    console.log(coinbase);

    var originalBalance = web3.eth.getBalance(coinbase).toNumber();
    var blocks = web3.eth.blockNumber;
    document.getElementById('coinbase').innerText = 'Me: ' + coinbase;
    document.getElementById('original').innerText = ' Original Eth ' + web3.fromWei(originalBalance) + '    watching...';
    document.getElementById('blocks').innerText = ' Blocks: ' +  blocks;  

    web3.eth.filter('latest').watch(function() {
        var currentBalance = web3.eth.getBalance(coinbase).toNumber();
        var blocks = web3.eth.blockNumber;
        document.getElementById("current").innerText = 'Current Eth ' + web3.fromWei(currentBalance);
        document.getElementById("diff").innerText = 'Difference:    ' + web3.fromWei(currentBalance - originalBalance);
        document.getElementById('blocks').innerText = ' Blocks: ' +  blocks; 
    });
}