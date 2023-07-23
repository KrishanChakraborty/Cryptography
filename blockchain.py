#Creation of a general blockchain

import datetime
import hashlib
import json
from flask import Flask, jsonify

# Step 1: Building the structutre of a general bloackchain

class Blockchain():
    
    def __init__(self):
        self.chain = []
        self.create_block(proof = 1 , previous_hash = '0')
        
    def create_block(self , proof , previous_hash):
        
        block = {'block_index' : len(self.chain)+1,
                  'timestamp' : datetime.datetime.now(),
                  'proof' : proof,
                  'previous_hash' : previous_hash
                 }
        self.chain.append(block)
        return block 
    
    def get_previous_block(self):
        return self.chain[-1]
    
    def proof_of_work(self , previous_proof):
        
        new_proof = 1
        #proof_status = False
        while True:
            hash_value = hashlib.sha256(str(new_proof**3 - previous_proof**2).encode()).hexdigest()
            
            if hash_value[:5]=='00000':
                return new_proof
            else:
                new_proof = new_proof + 1
                
    def get_block_hash(self , block):
        
        converted_block = json.dumps(str(block))
        block_hash = hashlib.sha256(converted_block.encode()).hexdigest()
        return block_hash
    
    def is_chain_valid(self , chain):
        
        previous_block = chain[0] 
        block_index = 1
        
        while block_index < len(chain) :
            
            current_block = chain[block_index]
            previous_proof = previous_block['proof']
            proof = current_block['proof']
            hash_value = hashlib.sha256(str(proof**3 - previous_proof**2).encode()).hexdigest()
            if hash_value[:5] != '00000':
                return False
            hash_value = self.get_block_hash(previous_block)
            if hash_value != current_block['previous_hash'] :
                return False 
            
            previous_block = current_block 
            block_index = block_index + 1 
            
        return True

            
# Step 2: Mining blocks to append it into the chain

blockchain = Blockchain()
app = Flask(__name__)
app.config['JSONIFY_PRETTYPRINT_REGULAR'] = False 
@app.route('/mine_block' , methods = ['GET'])

def mine_block():
    
    previous_block = blockchain.get_previous_block()
    previous_proof = previous_block['proof']
    proof = blockchain.proof_of_work(previous_proof)
    previous_hash = blockchain.get_block_hash(previous_block)
    
    block = blockchain.create_block(proof , previous_hash)
    
    response = {'status': "Congats! you have mined a block",
                'block_index' : block['block_index'],
                'timestamp' : block['timestamp'],
                'proof' : block['proof'],
                'hash of previous block' : block['previous_hash']
                }
    return jsonify(response) , 200

@app.route('/get_chain' , methods = ['GET'])

def get_chain():
    response = {'chain' : blockchain.chain,
                'no. of transactions in the chain' : len(blockchain.chain)
                }
    
    return jsonify(response) , 200 

@app.route('/chain_is_valid' , methods = ['GET'])

def chain_is_valid():
    
    chain = blockchain.chain 
    value = blockchain.is_chain_valid(chain)
    
    if value == True :
        response = {'status': 'All the transactions are valid in the chain',
                    'number of transactions' : len(chain)
                    }
        return jsonify(response) , 200
    else:
        response = {'status': 'The chain is defective',
                    'number of transactions' : len(chain)
                    }
        return jsonify(response) , 200
    
    
app.run(host= '0.0.0.0' , port = 5000)


        
         































