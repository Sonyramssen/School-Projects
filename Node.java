/*
 * 
 * This class holds the Node and all of its attributes, the string name = idata, the double GDPPC = ddata
 * the left child and the right child of the binary search tree;
 * 
 */
class Node{

public String idata; 
public double ddata;
public Node leftChild;
public Node rightChild;

/*
 * This method prints the countries that are being stored in the binary search tree 
 * 
 */
public void displayNode(){

    System.out.printf("%-33s %-30.3f\n",idata,ddata);

}

}