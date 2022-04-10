package homework;

import java.util.Arrays;

/*
Write a Java program to add two matrices of same size
Because The matrices can be entered by the user or constants.
-> so I will add 2 matrices of size 3x3
|1 2 3|       |7 6 5|
|3 4 5|   +   |5 4 3|
|5 6 7|       |3 2 1|
*/

public class exercise5_7 {
	public static void main(String[] args) {
		int[][] matrix1 = { { 1, 2, 3 }, { 3, 4, 5 }, { 5, 6, 7 } };
		int[][] matrix2 = { { 7, 6, 5 }, { 5, 4, 3 }, { 3, 2, 1 } };
		int[][] sum = new int[3][3];

		System.out.println("Matrix 1:");
		for (int i = 0; i < matrix1.length; i++) {
			System.out.println(Arrays.toString(matrix1[i]));
		}
		System.out.println("Matrix 2:");
		for (int i = 0; i < matrix2.length; i++) {
			System.out.println(Arrays.toString(matrix2[i]));
		}

		for (int i = 0; i < sum.length; i++) {
			for (int k = 0; k < sum.length; k++) {
				sum[i][k] = matrix1[i][k] + matrix2[i][k];
			}
		}

		System.out.println("Sum: ");
		for (int i = 0; i < sum.length; i++) {
			System.out.println(Arrays.toString(sum[i]));
		}
	}
}
