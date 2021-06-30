//package karenandmorning;

import java.util.*;
import java.io.*;

public class karenandmorning {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		String time = fin.readLine();
		int hour = Integer.parseInt(time.substring(0, 2));
		int min = Integer.parseInt(time.substring(3, 5));
		int ans = 0;
		while(true) {
			if(hour % 10 == min / 10 && min % 10 == hour / 10) {
				break;
			}
			min ++;
			if(min == 60) {
				min = 0;
				hour ++;
			}
			if(hour == 24) {
				hour = 0;
				min = 0;
			}
			ans ++;
		}
		System.out.println(ans);
	}
}
