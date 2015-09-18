package com.wawov.nativeapp.model;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Administrator on 2015/9/17 0017.
 */
public class Transportation {
    private static List<Container> containers = new ArrayList<>();

    public void add(Container container){
        containers.add(container);
    }

    public void remove(Container container){
        containers.remove(container);
    }

    public Container get(Container container){
        int index = containers.indexOf(container);
        return  containers.get(index);
    }
}
