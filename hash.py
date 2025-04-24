class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size
        self.element_count = 0
        self.comparisons = 0

    def hash_function(self, key):
        return key % self.size

    def linear_probe(self, key, data):
        index = self.hash_function(key)
        comparisons = 0
        while self.table[index] is not None:
            comparisons += 1
            index = (index + 1) % self.size
        self.table[index] = [key, data]
        self.element_count += 1
        self.comparisons += comparisons
        return index

    def quadratic_probe(self, key, data):
        index = self.hash_function(key)
        comparisons = 0
        i = 1
        while self.table[index] is not None:
            comparisons += 1
            index = (index + i * i) % self.size
            i += 1
        self.table[index] = [key, data]
        self.element_count += 1
        self.comparisons += comparisons
        return index

    def get(self, key, data, probing_type):
        index = self.hash_function(key)
        comparisons = 0
        if probing_type == "linear":
            while self.table[index] is not None:
                comparisons += 1
                if self.table[index][0] == key and self.table[index][1] == data:
                    self.comparisons += comparisons
                    return index
                index = (index + 1) % self.size
        elif probing_type == "quadratic":
            i = 1
            while self.table[index] is not None:
                comparisons += 1
                if self.table[index][0] == key and self.table[index][1] == data:
                    self.comparisons += comparisons
                    return index
                index = (index + i * i) % self.size
                i += 1
        self.comparisons += comparisons
        return None

    def insert(self, key, data, probing_type):
        if self.element_count == self.size:
            print("Table is full")
            return False

        if probing_type == "linear":
            index = self.linear_probe(key, data)
            print("Data inserted at", index)
            print(self.table)
        elif probing_type == "quadratic":
            index = self.quadratic_probe(key, data)
            print("Data inserted at", index)
            print(self.table)
        return True

    def menu(self):
        size = int(input("Enter size of hash table: "))
        self.__init__(size)
        probing_type = input("Enter probing type (linear/quadratic): ")
        while True:
            print("\nHash Table Menu")
            print("1. Insert")
            print("2. Search")
            print("3. Exit")
            choice = int(input("Enter your choice: "))
            if choice == 1:
                key = int(input("Enter phone number: "))
                data = input("Enter name: ")
                self.insert(key, data, probing_type)
            elif choice == 2:
                key = int(input("Enter key to be searched: "))
                data = input("Enter name: ")
                result = self.get(key, data, probing_type)
                if result is None:
                    print("Key not found")
                else:
                    print("Key found at", result)
            elif choice == 3:
                print("Exiting...")
                break
            else:
                print("Invalid choice. Please try again.")

if __name__ == "__main__":
    hash_table = HashTable(0)
    hash_table.menu()
