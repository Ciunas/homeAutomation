package com.example.ciunas.myapplication;

import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;

public class MainActivity extends AppCompatActivity {

    //public static final String URL = "http://localhost:25000";
    Button button1;
    Button button2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //Start service
        button2 = (Button) findViewById(R.id.button2);
        button2.setVisibility(View.VISIBLE);
        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                System.out.println("Running async task");
                FetchData task = new FetchData();
                task.execute();
            }
        });



        //Start service
        button1 = (Button) findViewById(R.id.button1);
        button1.setVisibility(View.VISIBLE);
        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {


            }
        });
    }

    private class FetchData extends AsyncTask<Void, Void, String> {

        @Override
        protected String doInBackground(Void... params) {
            // These two need to be declared outside the try/catch
            // so that they can be closed in the finally block.
            HttpURLConnection urlConnection = null;
            BufferedReader reader = null;
            // Will contain the raw JSON response as a string.
            String forecastJsonStr = null;

            System.out.println("running async");
            try {
                // Construct the URL
                java.net.URL url = new java.net.URL("http://192.168.1.24:1989");

                // Create the request to server, and open the connection
                urlConnection = (HttpURLConnection) url.openConnection();
                urlConnection.setRequestMethod("GET");
                urlConnection.connect();
                System.out.println("here");

                // Read the input stream into a String

                InputStream inputStream = urlConnection.getInputStream();

                StringBuffer buffer = new StringBuffer();
                if (inputStream == null) {
                    System.out.println("inputstream failed");
                    return null;
                }

                reader = new BufferedReader(new InputStreamReader(inputStream));

                String line;
                System.out.println("here");

                while ((line = reader.readLine()) != null) {
                    //System.out.println(line);
                    buffer.append(line + "\n");
                }

                if (buffer.length() == 0) {
                    System.out.println("Stream empty no data.");
                    return null;
                }

                System.out.println(" hello" + buffer.toString());
                return buffer.toString();

            } catch (IOException e) {

                System.out.println("Cannot connect");
                return null;
            } finally{
                if (urlConnection != null) {
                    urlConnection.disconnect();
                }
                if (reader != null) {
                    try {
                        reader.close();
                    } catch (final IOException e) {
                    }
                }
            }
        }

        @Override
        protected void onPostExecute(String s) {
            super.onPostExecute(s);
        }
    }
}
