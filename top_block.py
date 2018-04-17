#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Top Block
# Generated: Tue Aug 23 16:46:28 2016
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

from gnuradio import analog
from gnuradio import audio
from gnuradio import eng_notation
from gnuradio import filter
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from gnuradio.wxgui import forms
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import wx


class top_block(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Top Block")

        ##################################################
        # Variables
        ##################################################
        self.volume = volume = 0
        self.transition = transition = 10
        self.samp_rate = samp_rate = 32000
        self.low_freq = low_freq = 50
        self.high_freq = high_freq = 500

        ##################################################
        # Blocks
        ##################################################
        _volume_sizer = wx.BoxSizer(wx.VERTICAL)
        self._volume_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_volume_sizer,
        	value=self.volume,
        	callback=self.set_volume,
        	label='volume',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._volume_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_volume_sizer,
        	value=self.volume,
        	callback=self.set_volume,
        	minimum=0,
        	maximum=1,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.Add(_volume_sizer)
        _transition_sizer = wx.BoxSizer(wx.VERTICAL)
        self._transition_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_transition_sizer,
        	value=self.transition,
        	callback=self.set_transition,
        	label='transition',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._transition_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_transition_sizer,
        	value=self.transition,
        	callback=self.set_transition,
        	minimum=0,
        	maximum=100,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.Add(_transition_sizer)
        _low_freq_sizer = wx.BoxSizer(wx.VERTICAL)
        self._low_freq_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_low_freq_sizer,
        	value=self.low_freq,
        	callback=self.set_low_freq,
        	label='low_freq',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._low_freq_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_low_freq_sizer,
        	value=self.low_freq,
        	callback=self.set_low_freq,
        	minimum=0,
        	maximum=20e3,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.Add(_low_freq_sizer)
        _high_freq_sizer = wx.BoxSizer(wx.VERTICAL)
        self._high_freq_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_high_freq_sizer,
        	value=self.high_freq,
        	callback=self.set_high_freq,
        	label='high_freq',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._high_freq_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_high_freq_sizer,
        	value=self.high_freq,
        	callback=self.set_high_freq,
        	minimum=0,
        	maximum=20e3,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.Add(_high_freq_sizer)
        self.band_pass_filter_0 = filter.interp_fir_filter_fff(1, firdes.band_pass(
        	1, samp_rate, low_freq, high_freq, transition, firdes.WIN_HAMMING, 6.76))
        self.audio_sink_0 = audio.sink(32000, '', True)
        self.analog_noise_source_x_0 = analog.noise_source_f(analog.GR_GAUSSIAN, volume, 7829034597)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_noise_source_x_0, 0), (self.band_pass_filter_0, 0))    
        self.connect((self.band_pass_filter_0, 0), (self.audio_sink_0, 0))    

    def get_volume(self):
        return self.volume

    def set_volume(self, volume):
        self.volume = volume
        self._volume_slider.set_value(self.volume)
        self._volume_text_box.set_value(self.volume)
        self.analog_noise_source_x_0.set_amplitude(self.volume)

    def get_transition(self):
        return self.transition

    def set_transition(self, transition):
        self.transition = transition
        self._transition_slider.set_value(self.transition)
        self._transition_text_box.set_value(self.transition)
        self.band_pass_filter_0.set_taps(firdes.band_pass(1, self.samp_rate, self.low_freq, self.high_freq, self.transition, firdes.WIN_HAMMING, 6.76))

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.band_pass_filter_0.set_taps(firdes.band_pass(1, self.samp_rate, self.low_freq, self.high_freq, self.transition, firdes.WIN_HAMMING, 6.76))

    def get_low_freq(self):
        return self.low_freq

    def set_low_freq(self, low_freq):
        self.low_freq = low_freq
        self._low_freq_slider.set_value(self.low_freq)
        self._low_freq_text_box.set_value(self.low_freq)
        self.band_pass_filter_0.set_taps(firdes.band_pass(1, self.samp_rate, self.low_freq, self.high_freq, self.transition, firdes.WIN_HAMMING, 6.76))

    def get_high_freq(self):
        return self.high_freq

    def set_high_freq(self, high_freq):
        self.high_freq = high_freq
        self._high_freq_slider.set_value(self.high_freq)
        self._high_freq_text_box.set_value(self.high_freq)
        self.band_pass_filter_0.set_taps(firdes.band_pass(1, self.samp_rate, self.low_freq, self.high_freq, self.transition, firdes.WIN_HAMMING, 6.76))


def main(top_block_cls=top_block, options=None):

    tb = top_block_cls()
    tb.Start(True)
    tb.Wait()


if __name__ == '__main__':
    main()
