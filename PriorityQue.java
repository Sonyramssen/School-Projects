/*
 * 
 * The following class creates a priority que and stroes thebinary search tree so that the user can print the top and bottom countries within the binary search tree.
 * 
 * @author ramssen sony
 * @version 11/17/2022
 * 
 */
public class PriorityQue {

    public int maxSize;
    public Node[] queArray;
    public int nItems;


    /*
     * Priority que contructor that takes in the size and sets it 
     * 
     * @param int m - size of the que 
     */
public PriorityQue(int m){

    maxSize = m;
    queArray = new Node[maxSize];
    nItems = 0;

}

/*
* Insert method of the que that inserts every single node into the correct place so it that it can be shown within GDPPC 
* 
* @param Node obj - type of Node that is being passed from the tree 
*/
public void insertMethod(Node obj) {
		
    if(isFull()){

        System.out.println("");
        System.out.println("Country cannot be inserted the queue is Full!!!\n");
        System.out.println("");
    }

    else{int j;
    if(nItems == 0)
        queArray[nItems++] = obj;
    else {
        for(j = nItems-1;j>=0;j--) 
        {
            if(obj.ddata > queArray[j].ddata)
                queArray[j+1] = queArray[j];
            else 
                break;
        }
        queArray[j+1] = obj;
        nItems++;
    }
}
}

/*
* Que insert method which traverses through the tree from the left and right child 
* 
* @param Node localNode - the node that is being used to traverse throughout the tree 
*/
public void queInsert(Node localnNode){
    if(localnNode != null){
        queInsert(localnNode.leftChild);
        queInsert(localnNode.rightChild);
        insertMethod(localnNode);
    }
}

/*
 * 
 * This method checks if the que is empty at a certin given time 
 * 
 */
        public boolean isEmpty() {
            if(nItems == 0) {
                return true;
            }
            return false;
        }

/*
 * 
 * This method checks if the que is fill at a certain given time
 * 
 */
        public boolean isFull() {
		
            if(nItems == maxSize) {
                return true;
            }
            return false;
    }
    
}
