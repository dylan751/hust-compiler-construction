package exercise03;

import java.util.Scanner;
import java.lang.Math;

public class DrawTriangle {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		
		System.out.println("Input the height of the triangle: ");
		int triangleHeight = sc.nextInt();
		
		while(triangleHeight < 0) {
			System.out.println("Please input a number > 0!");
			triangleHeight = sc.nextInt();
		}
		
		for(int i = 0; i < triangleHeight; i++) {
			for(int j = 0; j < triangleHeight * 2 + 1; j++) {
				if(Math.abs(j - triangleHeight) <= i) {
					System.out.print("*");
				} else {
					System.out.print(" ");
				}
			}
			System.out.println("\n");
		}
		
		System.exit(0);
	}

}
