public class Constants2 {
	public static final double CM = 2.54;
	public static double SQRT(int x) {
		return Math.sqrt(x);
	}
	public static void main(String[] args) {
		double paperWidth = 8.5+1;
		double paperHeight = 11;
		System.out.println("Paper is:" + paperWidth + "\n" + paperWidth * CM);
		System.out.println(SQRT(16));

	}

}