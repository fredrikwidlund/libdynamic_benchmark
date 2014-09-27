#!/usr/sbin/Rscript

library(ggplot2)
library(scales)
library(sitools)

data.vector_grow_c <- read.csv("vector_grow_c.csv", head=TRUE, sep=",")
data.vector_grow_c_jemalloc <- read.csv("vector_grow_c_jemalloc.csv", head=TRUE, sep=",")
data.vector_grow_cpp <- read.csv("vector_grow_cpp.csv", head=TRUE, sep=",")
data.vector_grow_java_trove <- read.csv("vector_grow_java_trove.csv", head=TRUE, sep=",")
data.vector_grow_lua_assign <- read.csv("vector_grow_lua_assign.csv", head=TRUE, sep=",")
data.vector_grow_rust <- read.csv("vector_grow_rust.csv", head=TRUE, sep=",")
data.vector_grow_rust_no_jemalloc <- read.csv("vector_grow_rust_no_jemalloc.csv", head=TRUE, sep=",")

graph <- ggplot(legend = TRUE) +
  ggtitle('Vector benchmark') +
  theme(plot.title = element_text(size = 10),
        axis.title.x = element_text(size = 8), axis.title.y = element_text(size = 8),
        axis.text.x = element_text(size = 8), axis.text.y = element_text(size = 8)) + 
  geom_line(data = data.vector_grow_lua_assign      , aes(x = size, y = time, colour = "LuaJIT index assign")) +
  geom_line(data = data.vector_grow_cpp             , aes(x = size, y = time, colour = "C++ std::vector")) +
  geom_line(data = data.vector_grow_rust            , aes(x = size, y = time, colour = "Rust std::vec (jemalloc)")) +
  geom_line(data = data.vector_grow_c_jemalloc      , aes(x = size, y = time, colour = "C libdynamic vector (jemalloc)")) +
  geom_line(data = data.vector_grow_rust_no_jemalloc, aes(x = size, y = time, colour = "Rust std::vec (glibc allocator)")) +
  geom_line(data = data.vector_grow_c               , aes(x = size, y = time, colour = "C libdynamic vector (glibc allocator)")) +
  scale_y_continuous(labels = comma) +
  scale_x_continuous(breaks = seq(10^7, 10^8, 10^7), labels = f2si) +
  scale_colour_manual("",
                      limits = c("LuaJIT index assign",
                                 "C++ std::vector", "Rust std::vec (jemalloc)", "C libdynamic vector (jemalloc)", "Rust std::vec (glibc allocator)", "C libdynamic vector (glibc allocator)"),
                      values = c("#CC9933",
                                 "#006666", "#3399FF", "#993300", "#CCCC99", "#666666")) 
ggsave(graph, file = "vector_grow_linear.pdf", width = 10, height = 5)
