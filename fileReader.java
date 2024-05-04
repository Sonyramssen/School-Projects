package reader;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class fileReader {
	
	public static void main(String[] args) throws IOException {
		

		System.out.println("Please enter the name of the CSV file to be proccesed <FILENAME>: ");
	   
		
		List<List<String>> Lines = new ArrayList<>();
		try {
			try (Scanner scan = new Scanner(System.in)) {
				
				//Scanning for a file 
				String strLine = scan.next();
				//Reading into the file using a Buffered Reader
				BufferedReader br = new BufferedReader(new FileReader(strLine));
				
				System.out.println("Scanning for File....");
				System.out.println("Closing File Scanner");
				scan.close();
				System.out.println("Scanner closed!!!");
				
				System.out.println("");
				
				//Reading the file line by line and placing it into an array 
				while((strLine = br.readLine()) !=null) {			
					String[] parsedLines = strLine.split(",");
				
					for(String value : parsedLines) {
					
					//Printing content of file 
					System.out.printf("%-20s", value);		//Precision for alignment using printf();
					
					}
					
				System.out.println("");
					
				}		
				System.out.println("");
				System.out.println("Closing the File....");		
				br.close();			
				System.out.println("The File is Now Closed");

			}		
		} 
			catch (FileNotFoundException fnf) {
			// TODO Auto-generated catch block
			System.out.println("THE FILE COULD NOT BE FOUND");
		}
		
	}
}
