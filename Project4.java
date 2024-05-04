import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

/**
 * COP 3530: Project 4 - Binary Search Trees
 * This class includes a main class which reads in a csv file, the file name is a input value which is asked by the system  and inputed by the user, 
 * and reads through it parsing it after every iteration. This also creats an empty binary search tree.
 * 
 * After storing the array a menu withdifferent options is outputed to the user which is placed in a do while loop asking 
 * the user over and over again until they userInput == 9 which then exits the program. 
 * 
 * 
 * @author ramssen sony
 * @version 11/17/2022
 */
public class Project4{
	public final static int LeftPad = 10;
	static Project4 pgm = new Project4();
	static BinarySearchTree bs = new BinarySearchTree();
	static Node node = new Node();
	static PriorityQue pq = new PriorityQue(147);
	
/*
 * this is the main method which reads in a file and stores it in and stores the first and third valur which are the name and GDPPC, the main menu is also in this function which gets 
 * called repatitlty with the mainMenu() method.
 * This then fills the Binary Search tree with all the necessary information. 
 * @param string[] string value that stores 
 * @param args argument value 
 * @throws FIleNotFOund exception if user enters in the wrong file name.
 * 
 */
	public static void main(String[] args) throws Exception{

		System.out.println("COP3530 Project 4");
        System.out.println("Xudong Liu");

		System.out.print("Please enter the name of the File: ");	
		try {
		Scanner scan = new Scanner(System.in);

		
		String file = scan.nextLine();
			BufferedReader br = new BufferedReader(new FileReader(file));

			String line;
			int i = 0;

			br = new BufferedReader(new FileReader(file));
			line = br.readLine();


			while((line = br.readLine()) != null) {		
				
				String[] value = line.split(",");

				double GDPPC = Double.parseDouble(value[3]) / Double.parseDouble(value[2]);
				node.idata = value[0];
				node.ddata = GDPPC;
				bs.insert(value[0],GDPPC);
             }
			 	bs.insertqueMethod();


			 	System.out.println();
			 	System.out.println("There were 145 records read to build a binary search tree.");
				pgm.MainMenu();
				

	}catch(FileNotFoundException fne) {
		
		System.out.println("Invalid File Name, Please try Again: ");
		System.out.println();
			main(args);
		
	}
		
	}

	/*
	 * main menu that displays the different options to the user 
	 * this menu also asks the user to input information about a new country to insert into the binary search tree, delete, and traverse through it
	 * @throw InputMisMatchException if the user enters an inptu outisde of the menu range which is 1-9 
	 * 
	 * 
	 */
	public void MainMenu(){

		int usrInput;
		
		System.out.printf("Please choose one of the menu options.\n", LeftPad);	//menu regarding options 
		System.out.printf("1) Print tree inorder\n", LeftPad);
		System.out.printf("2) Print tree preorder \n", LeftPad);
		System.out.printf("3) Print tree postorder\n", LeftPad);
		System.out.printf("4) Insert a country with name and GDP per capita\n", LeftPad);
		System.out.printf("5) Delete a country for a given name\n", LeftPad);
		System.out.printf("6) Search and print a country and its path for a given name\n", LeftPad);
		System.out.printf("7) Print bottom countries regarding GDPPC\n", LeftPad);
		System.out.printf("8) Print top countries regarding GDPPC\n", LeftPad);
		System.out.printf("9) Exit\n", LeftPad);
		System.out.printf("Enter in your choice: \n",LeftPad);
		System.out.printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",LeftPad);

		Scanner input = new Scanner(System.in);
		usrInput = input.nextInt();
		System.out.println();
		
		
		try {
			
	switch(usrInput) {
	
	case 1: 
	bs.printInorder();
	pgm.MainMenu();
	break;

	case 2:
	bs.printPreorder();
	pgm.MainMenu();
	break;

	case 3: 
	bs.printPostorder();
	pgm.MainMenu();
	break;

	case 4: 
	Scanner name = new Scanner(System.in);
	System.out.print("Enter country name: \n");
	String nScan = name.nextLine();
	Scanner GD = new Scanner(System.in);
	System.out.print("Enter country GDP per capita: ");
	System.out.println();
	double Gdf = GD.nextDouble();
	bs.insert(nScan,Gdf);
	pgm.MainMenu();
	break;

	case 5: 
	Scanner sc = new Scanner(System.in);
	System.out.println("Enter country name: ");
	String scan = sc.next();
	System.out.println();
	Boolean num = bs.delete(scan);
	if(num == true){
		System.out.println(scan + " is deleted from binary search tree. ");
	}
	else System.out.println(scan + " was not found. ");
	pgm.MainMenu();
	break;

	case 6: 
	Scanner find = new Scanner(System.in);
	System.out.println("Enter country name: ");
	String findd = find.nextLine();
	System.out.println();
	double count = bs.find(findd);
	if(count == -1){
		System.out.println(findd + " is not found. ");
		System.out.println();
	}
	else{
		System.out.println();
	System.out.printf("%s is found with GDP per capita of %.3f" ,findd, count);
	System.out.println();
	}
	pgm.MainMenu();
	break;

	case 7: 
	Scanner bottom = new Scanner(System.in);
	System.out.print("Enter the number of countries: ");
	int number = bottom.nextInt();
	System.out.println();
	bs.printBottomCountries(number);
	pgm.MainMenu();
	break;

	case 8: 
	Scanner top = new Scanner(System.in);
	System.out.print("Enter the number of countries: ");
	int tnumber = top.nextInt();
	System.out.println();
	bs.printTopCountries(tnumber);
	pgm.MainMenu();
	break;


	case 9: 
		System.out.printf("Have a good day!", LeftPad);
		break;
		
	default: throw new InputMismatchException(); 

		}
		
		}
		catch(InputMismatchException ime) {
			System.out.println("Invalid choice! Enter 1-9: ");
			System.out.println();
			pgm.MainMenu();
		}

		}
	
}