package mixingwater;

import java.util.*;
import java.io.*;

public class mixingwaterver1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			double h = Integer.parseInt(st.nextToken());
			double c = Integer.parseInt(st.nextToken());
			double temp = Integer.parseInt(st.nextToken());
			long high = 1;
			long low = 1; //the amount of hot water cups
			while(((c * (high - 1)) + (h * high)) / (double) (high * 2 - 1) > temp) {
				high *= 2;
			}
			high *= 2;
			double minAbs = Math.abs((c + h) / 2d - temp);
			long min = 2;
			long mid = low + (high - low) / 2;
			while(low <= high) {
				double curTemp = ((c * (mid - 1)) + (h * mid)) / (double) (mid * 2 - 1);
				System.out.println(curTemp + " " + high + " " + low + " " + mid);
				if(Math.abs(curTemp - temp) < minAbs) {
					//System.out.println("CHANGE");
					minAbs = Math.min(minAbs, Math.abs(curTemp - temp));
					//System.out.println(mid * 2 - 1);
					min = mid * 2 - 1;
				}
				if(curTemp < temp) {
					high = mid;
				}
				else if(curTemp > temp) {
					low = mid;
				}
				else if(curTemp == temp) {
					break;
				}
				if(low + 1 == high) {
					System.out.println("LOW: " + low + " HIGH: " + high);
					if(Math.abs(((h + c) * (double) (low) - c) / (double)(low * 2 - 1) - temp) <= Math.abs(((h + c) * (double) (high) - c) / (double)(high * 2 - 1) - temp)){
						System.out.println(Math.abs(((h + c) * (double) (low) - c) / (double)(low * 2 - 1)) + " " + Math.abs(((h + c) * (double) (high) - c) / (double)(high * 2 - 1)));
						min = low * 2 - 1;
					}
					else if(minAbs > Math.abs(((h + c) * (double) (high) + h) / (double)(high * 2 + 1) - temp)){
						System.out.println("TRGE");
						min = high * 2 - 1;
					}
					break;
				}
				mid = low + (high - low) / 2;
			}
			//System.out.println(min);
			if(Math.abs((c + h) / 2d - temp) <= minAbs) {
				fout.append("2\n");
			}
			else {
				fout.append(min).append("\n");
			}
		}
		System.out.print(fout);
	}
}
