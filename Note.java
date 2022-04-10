
public class Note {
	public static void main(String[] args) {
		// 1. Note when using floating point
		System.out.println(2.0 - 1.1);
		System.out.println(5.0 - 4.1);
		
		// 2. printf in Java
		System.out.printf("%.2f\n", 2.0 - 1.1);
		
		// 3. Declare constant in Java
		final double PI = 3.14159;
		final long MICROS = 24 * 60 * 60 * 1000 * 1000; // Data overflow -> output of MICROS/MILLIS is wrong
		final long MILLIS = 24 * 60 * 60 * 1000;
		System.out.println(MICROS / MILLIS);
		
		// 4. Font
		System.out.println(12345 + 5432l);
	
		// 5. Parsing datatype
		System.out.println( (int) (char) (byte) -1); // char cannot be negative -> output is wrong
		
		// 6. char and String in addition
		System.out.println("H" + "a"); // String: Noi string
		System.out.println('H' + 'a'); // Char: Cong gia tri unicode;
		
		System.out.println(1 + 2 + "3");
		System.out.println("1" + 2 + 3); // Số hạng đầu là string -> các số sau đc chuyển thành string 
		
		// 7. Char in Java is unicode
		char a = '\u0061';
		System.out.println(a);
		
		ch\u0061r b = 'b'; // char b = 'b'
	}
	
}
