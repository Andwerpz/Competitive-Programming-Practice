//package compote;

import java.util.*;
import java.io.*;

public class compote {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int a = Integer.parseInt(fin.readLine());
		int b = Integer.parseInt(fin.readLine());
		int c = Integer.parseInt(fin.readLine());
		for(int i = 0; i < 252; i++) {
			if(a < i || b < i * 2 || c < i * 4) {
				System.out.println((i - 1) + (i - 1) * 2 + (i - 1) * 4);
				break;
			}
		}
	}
}
