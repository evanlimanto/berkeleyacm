import java.util.*;
import java.math.*;

public class BigInteger {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		BigInteger A = in.nextBigInteger();
		BigInteger B = in.nextBigInteger();
		A = A.add(B);
		System.out.println(A);
	}
}