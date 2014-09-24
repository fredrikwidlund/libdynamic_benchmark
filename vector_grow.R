#!/usr/sbin/Rscript 

library(ggplot2)
library(scales)
library(sitools)

data.vector_grow_c <- read.csv("vector_grow_c.csv", head=TRUE, sep=",")
data.vector_grow_cpp <- read.csv("vector_grow_cpp.csv", head=TRUE, sep=",")
data.vector_grow_java <- read.csv("vector_grow_java.csv", head=TRUE, sep=",")
data.vector_grow_java_trove <- read.csv("vector_grow_java_trove.csv", head=TRUE, sep=",")
data.vector_grow_lua <- read.csv("vector_grow_lua.csv", head=TRUE, sep=",")


graph <- ggplot(legend = TRUE) + 
  ggtitle('Vector benchmark') +
  theme(plot.title = element_text(size = 10), 
        axis.title.x = element_text(size = 8), axis.title.y = element_text(size = 8),
        axis.text.x = element_text(size = 8), axis.text.y = element_text(size = 8)) + 
  geom_line(data = data.vector_grow_c         , aes(x = size, y = time, colour = "C libdynamic vector")) +
  geom_line(data = data.vector_grow_cpp       , aes(x = size, y = time, colour = "C++ std::vector")) +
  geom_line(data = data.vector_grow_java      , aes(x = size, y = time, colour = "Java Vector<Integer>")) +
  geom_line(data = data.vector_grow_java_trove, aes(x = size, y = time, colour = "Java Trove TIntArrayList")) +
  geom_line(data = data.vector_grow_lua       , aes(x = size, y = time, colour = "LuaJIT")) +
  scale_y_continuous(trans = log_trans(), breaks = 10^(-3:2), labels = comma, minor_breaks = log(sapply(10^(-3:2), function(x) seq(0, x, x/10)))) +
  scale_x_continuous(breaks = seq(10^7, 10^8, 10^7), labels = f2si) +
  scale_colour_manual("",
                      breaks = c("Java Vector<Integer>", "Java Trove TIntArrayList", "LuaJIT", "C++ std::vector", "C libdynamic vector"),
                      values = c("#E69F00", "#56B4E9", "#009E73", "#0072B2", "#D55E00"))
ggsave(graph, file = "vector_grow.pdf", width = 10, height = 5)
