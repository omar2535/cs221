#include "chain.h"
#include "chain_given.cpp"

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain(){ /*your code here*/
    clear();
}

/**
 * Inserts a new node in position one of the Chain,
 * after the sentinel node.
 * This function **SHOULD** create a new Node.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertFront(const Block & ndata){
    Node* curr = new Node(ndata);
    Node* originalFront;
    if(head_->next!=NULL && head_->next != tail_){
        originalFront = head_->next;

        this->head_->next = curr;               
        curr->next = originalFront;
        originalFront->prev = curr;
        curr->prev = head_;
    }else{
        head_->next = curr;
        tail_->prev = curr;
        curr->next = tail_;
        curr->prev = head_;

    }

    length_++;
}

/**
 * Inserts a new node at the back of the Chain,
 * but before the tail sentinel node.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block & ndata){
   Node* curr = new Node(ndata);                 //Block given
   Node* previousNode = this->tail_->prev;       //making a copy with same address of last node
   if(previousNode != NULL && previousNode != head_){           //If last Node is not null
       previousNode->next = curr;                               //set the next block in the chian to be curr
       this->tail_->prev = curr;                                //set the last tail block to be the current one
       curr->prev = previousNode;
       curr->next = tail_;
   }else{
       this->head_->next = curr;
       this->tail_->prev = curr;
       curr->prev = head_;
       curr->next = tail_;
   }
   length_++;
}

/**
 * Modifies the Chain by moving a contiguous subset of Nodes to
 * the end of the chain. The subset of len nodes from (and
 * including) startPos are moved so that they
 * occupy the last len positions of the
 * chain (maintaining the sentinel at the end). Their order is
 * not changed in the move.
 */
void Chain::moveToBack(int startPos, int len){

    Node* start = walk(head_, startPos);
    // Node* end = walk(head_, len);
    // Node* startPrev = start->prev;
    // Node* endNext = end->next;
    // Node* beforeTail = tail_->prev;

    // if (start->prev != head_ && end->next != tail_ && start->prev != NULL && end->next != NULL) {

    // beforeTail->next = start;
    // start->prev = beforeTail;

    // end->next = tail_;
    // tail_->prev = end;
    
    // startPrev->next = endNext;
    // endNext->prev = startPrev;

    // }


     
    for (Node* curr = start; curr != NULL; curr = curr->next) {

        if (len != 0) {
          len --;
        }
        if (len == 0) {
          Node * end = curr;

          if (end->next != NULL && start->prev != NULL) {
            start->prev->next = end->next;
            end->next->prev = start->prev;


            start->prev = this->tail_->prev;
            end->next = this->tail_;
            this->tail_->prev->next = start;
            this->tail_->prev = end;
            
            }
        }
     }

}



/**
 * Rotates the current Chain by k nodes: removes the first
 * k nodes from the Chain and attaches them, in order, at
 * the end of the chain (maintaining the sentinel at the end).
 */
void Chain::rotate(int k){

    moveToBack(1,k);

}

/**
 * Modifies the current chain by swapping the Node at pos1
 * with the Node at pos2. the positions are 1-based.
 */
void Chain::swap(int pos1, int pos2){

   Node* node1 = walk(head_, pos1);
   Node* node2 = walk(head_, pos2);

   Node* node1next = node1->next;
   Node* node2next = node2->next;
   Node* node1prev = node1->prev;
   Node* node2prev = node2->prev;

   node1next->prev = node2;
   node1prev->next = node2;
   node2->next = node1next;
   node2->prev = node1prev;

   node2next->prev = node1;
   node2prev->next = node1;
   node1->next = node2next;
   node1->prev = node2prev; 

}

/*
 *  Modifies both the current and input chains by trading
 * nodes in even positions between the chains. Length
 * of each chain should stay the same. If the block dimensions
 * are NOT the same, the funtion has no effect and a simple
 * error message is output: cout << "Block sizes differ." << endl;
 */

void Chain::twist(Chain & other){
   
   for(int i=1; i<length_+1; i++){

       if(i%2==0){
            Node* thisNode = walk(head_, i);
            Node* otherNode = walk(other.head_, i);
            if(!(thisNode->data.width() != otherNode->data.width() && thisNode->data.height() != otherNode->data.height())){

            Node* thisNodePrev = thisNode->prev;
            Node* otherNodePrev = otherNode->prev;
            Node* thisNodeNext = thisNode->next;
            Node* otherNodeNext = otherNode->next;

            thisNodeNext->prev = otherNode;
            thisNodePrev->next = otherNode;
            otherNode->next = thisNodeNext;
            otherNode->prev = thisNodePrev;

            otherNodeNext->prev = thisNode;
            otherNodePrev->next = thisNode;
            thisNode->next = otherNodeNext;
            thisNode->prev = otherNodePrev;
            }else{
                std::cout<<"Block sizes differ."<<endl;
            }
       
       }
       
   }
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */

void Chain::clear() {
   Node* curr = head_->next;
   while(curr!= NULL){
       head_->next = curr->next;
       curr->next = NULL;
       delete(curr);
       curr = head_->next;
   }

}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */

void Chain::copy(Chain const& other) {
   this->head_ = new Node();
   this->head_ = other.head_;
   this->tail_ = new Node();
   this->tail_ = other.tail_;
   this->length_ = other.length_;
   this->height_ = other.height_;
   this->width_ = other.width_;
   
   Node* otherCurr = other.head_;
   Node* curr = this->head_;

   for(int i=1; i<other.length_; i++){
       Node* newNode = new Node();
       newNode = otherCurr->next;
       curr->next = newNode;
       curr = curr->next;
       otherCurr = otherCurr->next;
   }

}
