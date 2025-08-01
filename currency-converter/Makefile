
OBJECTS = obj/main.o obj/converter.o obj/api_client.o

output: $(OBJECTS)
	@mkdir -p bin
	g++ $(OBJECTS) -o bin/output -lcurl
	ln -sf bin/output output

obj:
	@mkdir -p obj

obj/%.o: src/%.cpp | obj
	g++ -Iinc -c $< -o $@

clean:
	rm -rf obj/*.o bin/output