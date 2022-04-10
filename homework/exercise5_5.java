package homework;

import java.util.Scanner;

public class exercise5_5 {
	// Function to convert String to integer
	public static int convert(String str) {
		int val = 0;
		// System.out.println("String = " + str);

		// Convert the String
		try {
			val = Integer.parseInt(str);
		} catch (NumberFormatException e) {

			// This is thrown when the String
			// contains characters other than digits
			System.out.println("Invalid Year " + str);
		}
		return val;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String month, StrYear;
		int IntYear;

		String[] MONTH = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "January", "February",
				"March", "April", "May", "June", "July", "August", "September", "October", "November", "December",
				"Jan.", "Feb.", "Mar.", "Apr.", "Aug.", "Sept.", "Oct.", "Nov.", "Dec.", "Jan", "Feb", "Mar", "Apr",
				"Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

		boolean invalidMonth = false;

		do {
			System.out.println("Month: ");
			month = sc.nextLine();
			for (int i = 0; i < MONTH.length; i++) {
				if (MONTH[i].equals(month)) {
					invalidMonth = true;
					break;
				}
			}
			System.out.println("Year: ");
			StrYear = sc.nextLine();
			if (invalidMonth == false) {
				System.out.println("Invalid month " + month);
			}
			IntYear = convert(StrYear);
		} while (invalidMonth == false || IntYear == 0);

		switch (month) {
		case "1", "3", "5", "7", "8", "10", "12", "January", "March", "May", "July", "August", "October", "December",
				"Jan.", "Mar.", "Aug.", "Oct.", "Dec.", "Jan", "Mar", "Jul", "Aug", "Oct", "Dec":
			System.out.println("This month has 31 days");
			break;
		case "4", "6", "9", "11", "April", "June", "September", "November", "Apr.", "Sept.", "Nov.", "Apr", "Jun",
				"Sep", "Nov":
			System.out.println("This month has 30 days");
			break;
		case "2", "February", "Feb.", "Feb":
			if (IntYear % 400 == 0 || (IntYear % 4 == 0 && IntYear % 100 != 0)) {
				System.out.println("This month has 29 days");
			} else {
				System.out.println("This month has 28 days");
			}
			break;
		}
		sc.close();
		System.exit(0);
	}
}
