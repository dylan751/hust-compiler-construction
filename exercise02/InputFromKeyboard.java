package exercise02;

import java.util.Scanner;

public class InputFromKeyboard {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		
		// Show message + read data
		System.out.println("Input your name: ");
		String strName = sc.nextLine();
		
		System.out.println("Input your age: ");
		int iAge = sc.nextInt();
		
		System.out.println("Input your height: ");
		double dHeight = sc.nextDouble();
		
		System.out.println("--- Your information ---");
		System.out.println("Name: " + strName + "\nAge: " + iAge + "\nHeight: " + dHeight);
	}

}
