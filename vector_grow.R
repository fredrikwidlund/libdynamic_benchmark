#!/usr/sbin/Rscript 

library(ggplot2)
library(scales)
library(sitools)

data.vector_grow_c <- read.csv("vector_grow_c.csv", head=TRUE, sep=",")
data.vector_grow_cpp <- read.csv("vector_grow_cpp.csv", head=TRUE, sep=",")
data.vector_grow_java_vector <- read.csv("vector_grow_java_vector.csv", head=TRUE, sep=",")
data.vector_grow_java_array_list <- read.csv("vector_grow_java_array_list.csv", head=TRUE, sep=",")
data.vector_grow_java_trove <- read.csv("vector_grow_java_trove.csv", head=TRUE, sep=",")
data.vector_grow_lua_table <- read.csv("vector_grow_lua_table.csv", head=TRUE, sep=",")
data.vector_grow_lua_assign <- read.csv("vector_grow_lua_assign.csv", head=TRUE, sep=",")
data.vector_grow_rust <- read.csv("vector_grow_rust.csv", head=TRUE, sep=",")

graph <- ggplot(legend = TRUE) + 
  ggtitle('Vector benchmark') +
  theme(plot.title = element_text(size = 10), 
        axis.title.x = element_text(size = 8), axis.title.y = element_text(size = 8),
        axis.text.x = element_text(size = 8), axis.text.y = element_text(size = 8)) + 
  geom_line(data = data.vector_grow_c              , aes(x = size, y = time, colour = "C libdynamic vector")) +
  geom_line(data = data.vector_grow_cpp            , aes(x = size, y = time, colour = "C++ std::vector")) +
  geom_line(data = data.vector_grow_java_vector    , aes(x = size, y = time, colour = "Java Vector<Integer>")) +
  geom_line(data = data.vector_grow_java_array_list, aes(x = size, y = time, colour = "Java ArrayList<Integer>")) +
  geom_line(data = data.vector_grow_java_trove     , aes(x = size, y = time, colour = "Java Trove TIntArrayList")) +
  geom_line(data = data.vector_grow_lua_table      , aes(x = size, y = time, colour = "LuaJIT table.insert()")) +
  geom_line(data = data.vector_grow_lua_assign     , aes(x = size, y = time, colour = "LuaJIT index assign")) +
  geom_line(data = data.vector_grow_rust           , aes(x = size, y = time, colour = "Rust vector")) +
  scale_y_continuous(trans = log_trans(), breaks = 10^(-3:2), labels = comma, minor_breaks = log(sapply(10^(-3:2), function(x) seq(0, x, x/10)))) +
  scale_x_continuous(breaks = seq(10^7, 10^8, 10^7), labels = f2si) +
  scale_colour_manual("",
                      breaks = c("LuaJIT table.insert()", "Java Vector<Integer>", "Java ArrayList<Integer>",
                                 "Java Trove TIntArrayList", "LuaJIT index assign", "Rust vector", "C++ std::vector", "C libdynamic vector"),
                      values = c("#E69F00", "#56B4E9", "#000000", "#009E73", "#F0E442", "#0072B2", "#D55E00", "#CC79A7"))
ggsave(graph, file = "vector_grow.pdf", width = 10, height = 5)
