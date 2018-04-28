
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"


/* given */
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL)
	{}

/* given */
twoDtree::~twoDtree(){
	clear();
}

/* given */
twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}

/* given */
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

/**
* Constructor that builds a twoDtree out of the given PNG.
* Every leaf in the tree corresponds to a pixel in the PNG.
* Every non-leaf node corresponds to a rectangle of pixels 
* in the original PNG, represented by an (x,y) pair for the 
* upper left corner of the rectangle and an (x,y) pair for 
* lower right corner of the rectangle. In addition, the Node
* stores a pixel representing the average color over the 
* rectangle. 
*
* Every node's left and right children correspond to a partition
* of the node's rectangle into two smaller rectangles. The node's
* rectangle is split by the horizontal or vertical line that 
* results in the two smaller rectangles whose sum of squared 
* differences from their mean is as small as possible.
*
* The left child of the node will contain the upper left corner
* of the node's rectangle, and the right child will contain the
* lower right corner.
*
* This function will build the stats object used to score the 
* splitting lines. It will also call helper function buildTree.
*/
twoDtree::twoDtree(PNG & imIn){
	stats myStat = stats(imIn);
	height = imIn.height();
	width = imIn.width();
	pair<int, int> ul = pair<int, int>(0,0);
	pair<int, int> lr = pair<int, int>(width-1, height-1);
	root = buildTree(myStat, ul, lr);
}


/**
* Private helper function for the constructor. Recursively builds
* the tree according to the specification of the constructor.
* @param s Contains the data used to split the rectangles
* @param ul upper left point of current node's rectangle.
* @param lr lower right point of current node's rectangle.
*/
twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr) {
	Node* currNode = new Node(ul, lr, s.getAvg(ul, lr));
	int firstX = ul.first;
	int firstY = ul.second;
	int secondX = lr.first;
	int secondY = lr.second;
	pair<int, int> minblock1lr = pair<int, int>(firstX, firstY);
	pair<int, int> minblock2ul = pair<int, int>(secondX, secondY);

	if(lr != ul){
		long minimized = s.getScore(ul, lr) + s.getScore(ul, lr);
		if(ul.first < lr.first){
			for(int x=firstX; x<=secondX-1; x++){
				pair<int, int> block1lr = pair<int, int>(x, secondY);
				pair<int, int> block2ul = pair<int, int>(x+1, firstY);
				int tempScore = s.getScore(ul, block1lr) + s.getScore(block2ul, lr);
				if(tempScore <= minimized){
					minimized = tempScore;
					minblock1lr = block1lr;
					minblock2ul = block2ul;
				}
			}
		}

		if(ul.second< lr.second){
			for(int y=firstY; y<=secondY-1; y++){
				pair<int, int>block1lr = pair<int, int>(secondX, y);
				pair<int, int>block2ul = pair<int, int>(firstX, y+1);
				int tempScore = s.getScore(ul, block1lr) + s.getScore(block2ul, lr);
				if(tempScore <= minimized){
					minimized = tempScore;
					minblock1lr = block1lr;
					minblock2ul = block2ul;
				}
			}
		}

		currNode->left = buildTree(s, ul, minblock1lr);
		currNode->right = buildTree(s, minblock2ul, lr);
	}
	return currNode;

}

/**
* Render returns a PNG image consisting of the pixels
* stored in the tree. may be used on pruned trees. Draws
* every leaf node's rectangle onto a PNG canvas using the 
* average color stored in the node.
*/
PNG twoDtree::render(){
	pair<int,int> ul = root->upLeft;                                              //
    pair<int,int> lr = root->lowRight;
    PNG * myPNG = new PNG(lr.first-ul.first+1, lr.second-ul.second+1);
	renderHelper(myPNG, root);
	return *myPNG;
}

void twoDtree::renderHelper(PNG * mypng, Node* currentNode){

	pair<int, int> ul = currentNode->upLeft;
	pair<int, int> lr = currentNode->lowRight;

	if(currentNode->left == NULL && currentNode->right == NULL){
		for(int x=ul.first; x<=lr.first; x++){
			for(int y=ul.second; y<=lr.second; y++){
				RGBAPixel* myPixel = mypng->getPixel(x,y);
				*myPixel = currentNode->avg;
			}
		}
	}
	if(currentNode->left != NULL){
		renderHelper(mypng, currentNode->left);
	}
	if(currentNode->right != NULL){
		renderHelper(mypng, currentNode->right);
	}
}


/*
*  Prune function trims subtrees as high as possible in the tree.
*  A subtree is pruned (cleared) if at least pct of its leaves are within 
*  tol of the average color stored in the root of the subtree. 
*  Pruning criteria should be evaluated on the original tree, not 
*  on a pruned subtree. (we only expect that trees would be pruned once.)
*  
* You may want a recursive helper function for this one.
*/
void twoDtree::prune(double pct, int tol){
	pruneHelperForTraversing(root, pct, tol);
}

int rectArea(pair<int,int> ul, pair<int,int> lr){
    	return (1 + lr.first - ul.first) * (1 + lr.second - ul.second);
}
void twoDtree::pruneHelperForTraversing(Node* topNode, double pct, int tol){
    double numLeaves = (double)pruneHelperForIndividualNode(topNode, topNode, tol);
    double area = (double)rectArea(topNode->upLeft, topNode->lowRight);
    double pctGot = numLeaves/area;
    if (pct <= pctGot) {
        if (topNode->left != NULL) {
            clearHelper(topNode->left);
            topNode->left = NULL;
        }
        if (topNode->right != NULL) {
            clearHelper(topNode->right);
            topNode->right = NULL;
        }
    }
    else {
        if (topNode->left != NULL) {
            pruneHelperForTraversing(topNode->left, pct, tol);
        }
        if (topNode->right != NULL) {
            pruneHelperForTraversing(topNode->right, pct, tol);
        }
    }
}

int twoDtree::pruneHelperForIndividualNode(Node* topNode, Node* currNode, int tol){
    if (currNode->left == NULL && currNode->right == NULL && pruneHelperForTolerance(topNode, currNode, tol)) {
        return 1;
    }
    if (currNode->left == NULL && currNode->right == NULL && !pruneHelperForTolerance(topNode, currNode, tol)) {
        return 0;
    }
    if (currNode->right != NULL && currNode->left != NULL) {
        return pruneHelperForIndividualNode(topNode, currNode->left, tol) + pruneHelperForIndividualNode(topNode, currNode->right, tol);
    }
    if (currNode->right == NULL && currNode->left != NULL) {
        return pruneHelperForIndividualNode(topNode, currNode->right, tol);
    }
    if (currNode->right != NULL && currNode->left == NULL) { 
        return pruneHelperForIndividualNode(topNode, currNode->left, tol);
    }
    else 
		return 0;
}

bool twoDtree::pruneHelperForTolerance(Node* topNode, Node* currNode, int tol){
    return ((currNode->avg.r - topNode->avg.r)*(currNode->avg.r - topNode->avg.r) + (currNode->avg.g - topNode->avg.g)*(currNode->avg.g - topNode->avg.g) + (currNode->avg.b - topNode->avg.b)*(currNode->avg.b - topNode->avg.b)) < tol;
}



/**
* Destroys all dynamically allocated memory associated with the
* current twoDtree class. Complete for PA3.
* You may want a recursive helper function for this one.
*/
void twoDtree::clear() {
	width = 0;
	height = 0;
	clearHelper(root);	
	delete root;
}

void twoDtree::clearHelper(Node* currentNode){
	if(currentNode->left != NULL){
		clearHelper(currentNode->left);
	}
	if(currentNode->right != NULL){
		clearHelper(currentNode->right);
	}
	currentNode->left = NULL;
	currentNode->right = NULL;
	delete currentNode->left;
	delete currentNode->right;

}

/**
* Copies the parameter other twoDtree into the current twoDtree.
* Does not free any memory. Called by copy constructor and op=.
* You may want a recursive helper function for this one.
* @param other The twoDtree to be copied.
*/
void twoDtree::copy(const twoDtree & other){	
	this->root = copyHelper(other.root);
	this->height = other.height;
	this->width = other.width;
}

twoDtree::Node* twoDtree::copyHelper(Node* otherNode){
	Node* result = new Node(otherNode->upLeft, otherNode->lowRight, otherNode->avg);

	if(otherNode->left != NULL){
		result->left = copyHelper(otherNode->left);
	}
	if(otherNode->right != NULL){
		result->right = copyHelper(otherNode->right);
	}
	return result;
}



