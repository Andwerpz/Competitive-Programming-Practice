//package antonanddanik;

import java.util.*;
import java.io.*;

public class antonanddanik {
	public static void main(String[] args) throws IOException {
		
		//734A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		char[] s = fin.readLine().toCharArray();
		int numAnton = 0;
		int numDanik = 0;
		for(int i = 0; i < n; i++) {
			numAnton += s[i] == 'A'? 1 : 0;
			numDanik += s[i] == 'D'? 1 : 0;
		}
		if(numAnton > numDanik) {
			System.out.println("Anton");
		}
		else if(numDanik > numAnton) {
			System.out.println("Danik");
		}
		else {
			System.out.println("Friendship");
		}
	}
}
