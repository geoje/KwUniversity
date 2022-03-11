package com.example.kwmp;

import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;

public class ListViewAdapter extends BaseAdapter {
    private final int TITLE = 0;

    ArrayList<ListViewItem> items = new ArrayList<>();

    @Override
    public int getCount() {
        return items.size();
    }

    @Override
    public Object getItem(int position) {
        return items.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public int getItemViewType(int position) {
        return items.get(position).getType();
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        final Context context = parent.getContext();

        if (convertView == null) {
            LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            ListViewItem item = items.get(position);

            switch (getItemViewType(position)) {
                case TITLE:
                    convertView = inflater.inflate(R.layout.listview_main, parent, false);
                    ((TextView)convertView.findViewById(R.id.tvTitle)).setText(item.getTitle());
                    ((TextView)convertView.findViewById(R.id.tvContent)).setText(item.getContent());
                    break;
            }
        }

        return convertView;
    }

    public void addItem(String title, String content, Intent intent) {
        ListViewItem item = new ListViewItem();
        item.setType(TITLE);
        item.setTitle(title);
        item.setContent(content);
        item.setIntent(intent);
        items.add(item);

        if (intent != null)
            intent.putExtra("title", title);
    }
}
