/// @title: Create a signed transaction using an account's private key
/// @author: Amay Kataria
/// @date: July 26, 2018

var Tx = require('ethereumjs-tx');
const Web3 = require('web3');
const web3 = new Web3('https://mainnet.infura.io/v3/24b152bca7704bf39741eed185972f92');

const account1 = '0x50f8be0A651a5F930c460BF7675fa0493F087967';
const account2 = '0x4Ae52740cB65c23e2634B3aFfBeb9f090f852Ebe';

const privateKey1 = Buffer.from(process.env.PRIVATE_KEY_1, 'hex'); 
const privateKey2 = Buffer.from(process.env.PRIVATE_KEY_2, 'hex'); 

web3.eth.getTransactionCount(account1, (err, txCount) => {
    // Build the transaction. 
    const txObject = {
        nonce: web3.utils.toHex(txCount),
        to: account2,
        value: web3.utils.toHex(web3.utils.toWei('0', 'ether')),
        gasLimit: web3.utils.toHex(30000),
        gasPrice: web3.utils.toHex(web3.utils.toWei('10', 'gwei')),
        data: web3.utils.toHex("I Am Alive. July 26, 2018. 11:06pm. Amay Kataria.")
    };

    // // Sign the transaction. 
    const tx = new Tx(txObject);
    tx.sign(privateKey1);

    // Serialize the transaction. Create raw transaction. 
    const serializedTransaction = tx.serialize(); 
    const raw = '0x' + serializedTransaction.toString('hex');

    // Broadcast the transaction
    web3.eth.sendSignedTransaction(raw, (err, txHash) => {
        console.log(err);
        console.log('Transaction:', txHash);
    });
});
