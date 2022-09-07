public class StaticTest{
	public static void main(String[] args){
		Employee[] staff = new Employee[3];

		staff[0] = new Employee("Tom",40000);
		staff[1] = new Employee("Dicm",40000);
		staff[2] = new Employee("Harry",65000);

		for(Employee e: staff)
			System.out.println("name="+e.getName());


	}
}

class Employee{
	private static int nextID = 1;

	private String name;
	private double salary;
	private int id;

	public Employee(String n, double s){
		name = n;
		salary = s;
		id = advanceID();
	}

	public String getName(){
		return name;
	}

	public double getSalary(){
		return salary;
	}

	public int getId(){
		return id;
	}

	public static int advanceID(){
		int r = nextID;
		nextID++;
		return r;
	}

	public static void main(String[] args){
		Employee e = new Employee("Harry",50000);
		System.out.println(e.getName()+" "+e.getSalary());
	}
}