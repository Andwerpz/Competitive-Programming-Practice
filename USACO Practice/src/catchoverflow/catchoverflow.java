//package catchoverflow;

import java.util.*;
import java.io.*;

public class catchoverflow {
	public static void main(String[] args) throws IOException {
		
		//1175B
		
		//all you have to do is simulate the program. If the value ever goes above 2^32 - 1, then break, and return an overflow error
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int l = Integer.parseInt(fin.readLine());
		Stack<Long> values = new Stack<Long>();
		Stack<Long> temp = new Stack<Long>();
		long sum = 0;
		long max = (long) (Math.pow(2, 32) - 1);
		boolean isValid = true;
		values.push(0l);
		for(int i = 0; i < l; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			String next = st.nextToken();
			if(next.equals("add")) {
				values.set(values.size() - 1, values.peek() + 1);
			}
			else if(next.equals("end")) {
				long value = values.pop() * temp.pop();
				values.set(values.size() - 1, values.peek() + value);
			}
			else {
				long multiplier = Integer.parseInt(st.nextToken());
				temp.add(multiplier);
				values.add(0l);
			}
			if(values.peek() > max) {
				isValid = false;
				break;
			}
		}
		if(values.peek() <= max && isValid) {
			System.out.println(values.peek());
		}
		else {
			System.out.println("OVERFLOW!!!");
		}
	}
}
