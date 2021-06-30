//package planetlapituletti;

import java.util.*;
import java.io.*;

public class planetlapituletti {
	public static void main(String[] args) throws IOException {
		
		//1493B
		
		//all you have to do is take in the initial time, and then just increment minute by minute, and stop when you see the first valid time.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		HashMap<Integer, Integer> key = new HashMap<Integer, Integer>();	//if a digit has a valid flip, stores the value of that flip
		key.put(0, 0);
		key.put(1, 1);
		key.put(2, 5);
		key.put(5, 2);
		key.put(8, 8);
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int h = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			boolean done = false;
			st = new StringTokenizer(fin.readLine());
			int hour = Integer.parseInt(st.nextToken(":"));
			int min = Integer.parseInt(st.nextToken());
			int shour = 0;
			int smin = 0;
			while(!done) {
				//System.out.println(hour + ":" + min);
				boolean isValid = true;
				int temp = hour;
				if(key.containsKey(temp % 10)) {
					smin = key.get(temp % 10) * 10;
					temp /= 10;
					if(key.containsKey(temp)) {
						smin += key.get(temp);
						temp = min;
						if(key.containsKey(temp % 10)) {
							shour = key.get(temp % 10) * 10;
							temp /= 10;
							if(key.containsKey(temp)) {
								shour += key.get(temp);
								if(smin >= m || shour >= h) {
									isValid = false;
								}
							}
							else {
								isValid = false;
							}
						}
						else {
							isValid = false;
						}
					}
					else {
						isValid = false;
					}
				}
				else {
					isValid = false;
				}
				if(isValid) {
					break;
				}
				else {
					min ++;
					if(min == m) {
						min = 0;
						hour ++;
					}
					if(hour == h) {
						hour = 0;
					}
				}
			}
			//System.out.println("VALID");
			fout.append((hour < 10? "0" : "") + hour + ":" + (min < 10? "0" : "") + min);
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
