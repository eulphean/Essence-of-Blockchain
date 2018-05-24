const Web3 = require('web3')
var web3 = new Web3('http://localhost:8545');


const main = async () => {
  const me = (await web3.eth.getAccounts())[0]
  console.log(me);
  var balance = await web3.eth.getBalance(me);
  console.log(balance);
}

main()
  .catch((error) => {
    console.error(error)
    process.exit(1)
  })
