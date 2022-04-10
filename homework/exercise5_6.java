package homework;

/*
Write a Java program to sort a numeric array, and calculate the sum and average value of array elements.
Because the array can be entered by the user or a constant -> I use a constant array
*/

import java.util.Arrays;

public class exercise5_6 {
	public static void main(String[] args) {
		// Scanner sc = new Scanner(System.in);
		int[] arr = { 1789, 2035, 1899, 1456, 2013 };
		System.out.println("Array: " + Arrays.toString(arr));
		// sort array
		Arrays.sort(arr);
		System.out.println("Sorted Array: " + Arrays.toString(arr));

		// calculate sum and average
		double sum = arr[0];
		for (int i = 1; i < arr.length; i++) {
			sum += arr[i];
		}
		System.out.println("Sum: " + sum);
		System.out.println("Average: " + (sum / arr.length));
		// sc.close();
		System.exit(0);
	}
}
