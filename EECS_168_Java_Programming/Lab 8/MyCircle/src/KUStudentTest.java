import java.util.Scanner;
public class KUStudentTest {

	public static void main(String[] args) {
		String fname;
		String lname;
		String kuid;
		String dpt;
		KUStudent ku=new KUStudent();
		Scanner myScan=new Scanner(System.in);
		System.out.println("Please input the student's name (firstname lastname):");
		fname=myScan.next();
		lname=myScan.next();
		System.out.println("Please input the student's KUID and department:");
		kuid=myScan.next();
		dpt=myScan.next();
		ku.set_name(fname,lname);
		ku.set_kuinfo(kuid, dpt);
		System.out.println("");
		System.out.println("Student: "+ku.get_fname()+" "+ku.get_lname());
		System.out.println("KUID "+ku.get_id());
		System.out.println("Department: "+ku.get_dpt());
		
	}

}
