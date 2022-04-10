package exercise01;

import javax.swing.JOptionPane;

public class ChoosingOption {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int option = JOptionPane.showConfirmDialog(null, "Do you want to ...?");
		JOptionPane.showMessageDialog(null, "You've chosen: "
				+ (option == JOptionPane.YES_OPTION ? "Yes" : (option == JOptionPane.CANCEL_OPTION ? "Cancel" : "No")));
		System.exit(0);
	}

}
