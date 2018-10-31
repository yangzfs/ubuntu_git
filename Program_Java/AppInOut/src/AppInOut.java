import java.awt.*;
import java.awt.event.*;

public class AppInOut {
    public static void main(String args[]){
        new FrameInOut();
    }
}

class FrameInOut extends Frame implements ActionListener{
    Label prompt;
    TextField input,output;
    Button btn;
    FrameInOut(){
        super("图形用户界面的java Appliction程序");
        prompt=new Label("请输入你的名字:"); //创建标签
        input=new TextField(6); //创建文本框
        output=new TextField(20); //创建文本框
        btn=new Button("关闭"); //创建按钮
        setLayout(new FlowLayout()); //界面上的图形对象的布局策略
        add(prompt);
        add(input);
        add(output);
        add(btn);
        input.addActionListener(this); //向事件监听者注册
        btn.addActionListener(this); //向事件监听者注册
        setSize(300,200);
        show();
    }
    public void actionPerformed(ActionEvent e){
        if(e.getSource()==input) //判断事件源
            output.setText(input.getText()+",欢迎进入java世界!");
        else{
            dispose();
            System.exit(0);
        }
    }
}