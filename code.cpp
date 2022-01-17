#include <iostream>
using namespace std;

//Structure to represent a fraction
struct Fraction{
    float N;//NUMERATOR
    float D;//DENOMINATOR
};
//Structure to represent a Node in a Tree.
struct Node {
    Fraction data;
    Node *leftChild;
    Node * rightChild;
};
//add function takes two fractions as parameters and returns the result of their summation.
Fraction add(Fraction x,Fraction y){
    Fraction result;//
    result.N = x.N + y.N;
    result.D = x.D + y.D;
    return result;
}
//createNode function allocates and returns a new node with the given data and the left and right pointer as NULL.
Node * createNode(Fraction value){
    Node * newNode  = new Node;//declaring and allocating memory for a node
    //Assigning values
    (newNode ->data)=value;
    newNode ->leftChild=newNode ->rightChild= NULL;
    return newNode; //returns a pointer to the new node
}
//Insert function add the created node into the tree after traversing the tree to find its place.
void Insert(Node *root, Node *p)
{
    Node*  father = root, *child = root;
    float NodeResult;
    NodeResult = p->data.N / p->data.D;
    while(child!=NULL)
    {
        father = child;
        if(NodeResult < 1)
            child = father->leftChild;
        else
            child = father->rightChild;
    } //end while
    if(NodeResult < (father->data.N/father->data.D))
        father->leftChild = p;
    else
        father->rightChild = p;
}

/*SB_representation function takes 4 parameters .
 * 1st -> Starting node (root).
 * 2ed -> input Fraction (the fraction that need to find the SB-representation for ).
 * 3rd -> left  Fraction is above root that has x in its right subtree.
 * 4th -> right Fraction is above root that has x in its left subtree.

 *Inside the function :

 * -Declare a pointer of type Node .
 * if root is equal to input delete the hole tree and terminate the function.

 * if input > root
 * -print R and create a new node with summation of the root and the right fraction
 * -insert it to the tree.
 * -update left fraction to have the value of root.
 * -update root to have the value of the new node.
 * call the function again with updated values of root and leftFraction.
 *
 * else
 * -print L and create a new node with summation of the root and the left fraction.
 * -insert it to the tree.
 * -update right fraction to have the value of root.
 * -update root to  have the value of the new node.
 *  call the function again with updated values of root and rightFraction.
*/
void SB_representation(Node* root,Fraction input,Fraction leftFraction,Fraction rightFraction){
    Node * newNode;

    if((input.N/input.D)==(root->data.N/root->data.D))return;

    if((input.N/input.D) > (root->data.N/root->data.D)){
        cout<<'R';
        newNode =createNode(add(root->data,rightFraction));
        Insert(root,newNode);
        leftFraction = root->data;
        root=newNode;
        SB_representation(root, input, leftFraction,rightFraction);
    }
    else{
        cout<<'L';
        newNode =createNode(add(root->data,leftFraction));
        Insert(root, newNode);
        rightFraction = root->data;
        root=newNode;
        SB_representation(root, input, leftFraction,rightFraction);
    }
}

// Recursive function to return Greatest Common Divisor of a and b
int GCD(int a, int b) {
    if (b == 0) {
        return a;
    }
    if (a < b) {
        return GCD(b, a);
    }
    return GCD(b, a % b);
}
// isNumeric function validate the input if it has anything else but digit.
bool isNumeric(int x, int y) {
    string str = to_string(x)+ to_string(y);
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;

    return true;
}
int main(){

    Node * root; //declaring a node

    Fraction left,right,input;//declaring fractions

    //initializing fractions
    left.N = 0;left.D=1;
    right.N=1;right.D=0;

    //initializing the root of the BST with the ????
    root = createNode(add(left,right));

    // take fraction as an input.
    cin>>input.N>>input.D;
    // while the input does not equal to two 1's.
    while(input.N!=1 || input.D!=1){

        //check if the input is not relatively prime or not a numeric exit
        if(GCD(input.N, input.D)>1 || !isNumeric(input.N, input.D)){
            cout << endl << "ERROR: Invalid data" << endl;
            exit(0);
        }
        //find the Stern-Brocot number system representation of the input fraction.
        SB_representation(root,input,left,right);
        //print new line
        cout<<"\n";
        //take fraction as an input.
        cin>>input.N>>input.D;
    }
    return 0;
}
