
/*
 * This is a Link2 class that just sets the links. 
 * it delclares 3 different declarations the Country dData which is just the obj inside the country 
 * and the Link next which is referenced to access the next thing inside first, last, and current. etc.. and finally the previous which 
 * refers to the previous node in the list.
 * 
 * @author ramssen sony
 * @version 10/27/2022
 */
class Link3{

	public double GDPPC;
	public Link3 next;
	public Link3 previous;

/*
 * This method sets dData to everything that is stored inside the Country obj
 * 
 * @param Country obj
 * 
 */
	public Link3(double GDPPC){

		GDPPC = GDPPC;
	}
}
