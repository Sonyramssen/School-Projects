public class DoublyLinked {
    
public Link2 first; 
public Link2 last;

public DoublyLinked(){

last = null;
first = null;
}

public boolean isEmpty(){

    return first == null;

}

public void insertlast(Country obj){

    Link2 newLink2 = new Link2(obj);
    Link2 current = first;
    Link2 previous = null;
   
    while(current != null && obj.getCOVIDdeaths() / obj.getPopulation() * 100000 > current.dData2.getCOVIDdeaths() / current.dData2.getPopulation() * 100000)
    {
        previous = current;
        current = current.next;
    }
    if(previous == null)
    first = newLink2;
    else 
    previous.next = newLink2;
    newLink2.next = current;
}

public Link2 deleteFirst(){

    Link2 temp = first;
    if(first.next == null)
    last = null;
    else 
    first.next.previous = null;
    first = first.next;
    return temp;
}

}
