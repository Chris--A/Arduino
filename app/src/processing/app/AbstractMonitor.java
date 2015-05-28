package processing.app;

import static processing.app.I18n._;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.AbstractAction;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.KeyStroke;
import javax.swing.SwingUtilities;
import javax.swing.Timer;
import javax.swing.border.EmptyBorder;
import javax.swing.text.DefaultCaret;

import processing.app.debug.TextAreaFIFO;
import processing.app.legacy.PApplet;

@SuppressWarnings("serial")
public abstract class AbstractMonitor extends JFrame implements ActionListener {

  private boolean monitorEnabled;
  private boolean closed;

  private StringBuffer updateBuffer;
  private Timer updateTimer;

  public AbstractMonitor(String title) {
    super(title);

    addWindowListener(new WindowAdapter() {
      public void windowClosing(WindowEvent event) {
        try {
          closed = true;
          close();
        } catch (Exception e) {
          // ignore
        }
      }
    });

    // obvious, no?
    KeyStroke wc = Editor.WINDOW_CLOSE_KEYSTROKE;
    getRootPane().getInputMap(JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT).put(wc, "close");
    getRootPane().getActionMap().put("close", (new AbstractAction() {
      public void actionPerformed(ActionEvent event) {
        try {
          close();
        } catch (Exception e) {
          // ignore
        }
        setVisible(false);
      }
    }));


    onCreateWindow(getContentPane());

    this.setMinimumSize(new Dimension(getContentPane().getMinimumSize().width, this.getPreferredSize().height));

    pack();

    Dimension screen = Toolkit.getDefaultToolkit().getScreenSize();
    if (PreferencesData.get("last.screen.height") != null) {
      // if screen size has changed, the window coordinates no longer
      // make sense, so don't use them unless they're identical
      int screenW = PreferencesData.getInteger("last.screen.width");
      int screenH = PreferencesData.getInteger("last.screen.height");
      if ((screen.width == screenW) && (screen.height == screenH)) {
        String locationStr = PreferencesData.get("last.serial.location");
        if (locationStr != null) {
          int[] location = PApplet.parseInt(PApplet.split(locationStr, ','));
          setPlacement(location);
        }
      }
    }

    updateBuffer = new StringBuffer(1048576);
    updateTimer = new Timer(33, this);  // redraw serial monitor at 30 Hz
    updateTimer.start();

    monitorEnabled = true;
    closed = false;
  }
  
  protected abstract void onCreateWindow(Container mainPane);

  public void enableWindow(boolean enable)
  {
    onEnableWindow(enable);
    monitorEnabled = enable;
  }
  
  protected abstract void onEnableWindow(boolean enable);

  // Puts the window in suspend state, closing the serial port
  // to allow other entity (the programmer) to use it
  public void suspend()
  {
   enableWindow(false);

   try {
        close();
      }
   catch(Exception e) {
       //throw new SerialException("Failed closing the port");
   }

  }

  public void resume() throws SerialException
  {
    // Enable the window
    enableWindow(true);

    // If the window is visible, try to open the serial port
    if (isVisible())
      try {
        open();
      }
      catch(Exception e) {
	  throw new SerialException("Failed opening the port");
      }

  }

  protected void setPlacement(int[] location) {
    setBounds(location[0], location[1], location[2], location[3]);
  }

  protected int[] getPlacement() {
    int[] location = new int[4];

    // Get the dimensions of the Frame
    Rectangle bounds = getBounds();
    location[0] = bounds.x;
    location[1] = bounds.y;
    location[2] = bounds.width;
    location[3] = bounds.height;

    return location;
  }

  public abstract void message(final String s);

  public boolean requiresAuthorization() {
    return false;
  }

  public String getAuthorizationKey() {
    return null;
  }

  public boolean isClosed() {
      return closed;
  }

  public abstract void open() throws Exception;

  public abstract void close() throws Exception;

  public synchronized void addToUpdateBuffer(char buff[], int n) {
    updateBuffer.append(buff, 0, n);
  }

  private synchronized String consumeUpdateBuffer() {
    String s = updateBuffer.toString();
    updateBuffer.setLength(0);
    return s;
  }
  
  public void actionPerformed(ActionEvent e) {
    final String s = consumeUpdateBuffer();
    if (s.length() > 0) {
      message(s);
    }
  }
}
