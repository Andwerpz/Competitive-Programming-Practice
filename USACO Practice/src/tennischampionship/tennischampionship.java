//package tennischampionship;

import java.util.*;
import java.io.*;

public class tennischampionship {
	public static void main(String[] args) throws IOException {
		
		//735C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		long n = Long.parseLong(fin.readLine());
		ArrayList<Long> dp = new ArrayList<Long>();
		dp.add((long) 2);
		dp.add((long) 3);
		while(dp.get(dp.size() - 1) < n) {
			dp.add(dp.get(dp.size() - 1) + dp.get(dp.size() - 2));
			//System.out.println(dp.get(dp.size() - 1));
		}
		if(n == 2) {
			System.out.println(1);
		}
		else if(n <= 4) {
			System.out.println(2);
		}
		else {
			if(dp.get(dp.size() - 1) == n) {
				System.out.println(dp.size());
			}
			else {
				System.out.println(dp.size() - 1);
			}
		}
	}
}
