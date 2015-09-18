package com.wawov.nativeapp.model;

/**
 * Created by Administrator on 2015/9/17 0017.
 */
public class Container{

    private int id;
    private String name;
    private boolean expire;

    public Container(){}

    public Container(int id,String name,boolean expire){
        this.id = id;
        this.name = name;
        this.expire = expire;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public boolean isExpire() {
        return expire;
    }

    public void setExpire(boolean expire) {
        this.expire = expire;
    }


    @Override
    public boolean equals(Object o) {
        Container container = (Container)o;
        if(container.getId() == this.getId()){
            return true;
        }
        return false;
    }
}
