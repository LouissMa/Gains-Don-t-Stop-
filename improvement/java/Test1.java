public class Test1 {
    public static void main(String[] args) {
        Dog dog = new Dog("旺财", "黄色");
        // 优化：打印属性值，否则调用 getName 无实际效果
        System.out.println(dog.getName());
        System.out.println(dog.getColor());
        dog.eat();
        dog.swim();
    }

    // 修复：添加 static 修饰符，变为静态内部类
    static abstract class Animal {
        private String name;
        private String color;

        public Animal() {}
        public Animal(String name, String color) {
            this.name = name;
            this.color = color;
        }
        public String getName() {
            return name;
        }
        public void setName(String name) {
            this.name = name;
        }
        public String getColor() {
            return color;
        }
        public void setColor(String color) {
            this.color = color;
        }
        public abstract void eat();
    }

    interface Swim {
        void swim();
    }

    // 修复：添加 static 修饰符
    static class Rabbit extends Animal {
        public Rabbit() {}
        public Rabbit(String name, String color) {
            super(name, color);
        }
        @Override
        public void eat() {
            System.out.println("吃胡萝卜");
        }
    }

    // 修复：添加 static 修饰符
    static class Dog extends Animal implements Swim {
        public Dog() {}
        public Dog(String name, String color) {
            super(name, color);
        }
        @Override
        public void eat() {
            System.out.println("吃骨头");
        }
        @Override
        public void swim() {
            System.out.println("狗刨");
        }
    }
}